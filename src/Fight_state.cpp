#include <Fight_state.hpp>

Fight_state::Fight_state()
{
}

Fight_state::Fight_state(const std::string path, Game_system *game_sys_)
{
    this->background_texture.loadFromFile(path);
    this->background_sprite.setTexture(background_texture);
    this->background_sprite.setPosition(sf::Vector2f(0, 0));
    game_sys = game_sys_;

    enemy_texture.loadFromFile(goblin_image);
    enemy_sprite.setTexture(enemy_texture);
    enemy_sprite.setPosition(sf::Vector2f(925, 200));
    player_stats = game_sys->get_player_stats();

    statistics enemy_stats;
    enemy_stats.strength = 5;
    enemy_stats.dexterity = 5;
    enemy_stats.vitality = 5;
    enemy = std::make_unique<Enemy>(game_sys->get_enemy_type(), enemy_stats);

    std::unique_ptr<action_button> attack_but = std::make_unique<action_button>(attack_button, sf::Vector2f(200, 600), action_type::Attack);
    std::unique_ptr<action_button> heal_but = std::make_unique<action_button>(defend_button, sf::Vector2f(800, 600), action_type::Defend);
    std::unique_ptr<action_button> spell_but = std::make_unique<action_button>(spell_button, sf::Vector2f(1500, 600), action_type::Spell);

    buttons.push_back(std::move(attack_but));
    buttons.push_back(std::move(heal_but));
    buttons.push_back(std::move(spell_but));

    std::unique_ptr<Enemy_stats> enemy_window = std::make_unique<Enemy_stats>(enemy_statss, sf::Vector2f(1500, 200), change_to_map());
    e_s = enemy_window.get();
    interface_elements.push_back(std::move(enemy_window));
}

Fight_state::~Fight_state()
{
}

void Fight_state::render(sf::RenderWindow &window)
{

    window.draw(this->background_sprite);
    for (auto &ptr : interface_elements)
    {
        ptr.get()->render(window);
    }
    window.draw(this->enemy_sprite);
    for (auto &button : buttons)
    {
        button->render(window);
    }
}

void Fight_state::update()
{
    if (check_if_button_pressed())
    {
        if (action_to_be_performed != action_type::None)
        {
            if (action_to_be_performed == action_type::Attack)
            {
                int some_value = (attack(turn::player) - defend(turn::enemy));
                enemy->change_hp(some_value);
            }
            else if (action_to_be_performed == action_type::Spell)
            {
                int some_value = (spell(turn::player) - defend(turn::enemy));
                enemy->change_hp(some_value);
            }
            else if (action_to_be_performed == action_type::Defend)
            {
                int some_value = additional_defense(turn::player);
                player_stats.hp += some_value;
            }
            enemy_turn();
        }
        e_s->update_stats(change_to_map());
    }
    if (enemy->get_stats().hp <= 0)
    {
        s_manager->sygnalize_to_pop();
        game_sys->stop_fight();
        game_sys->set_last_fight_status("win");
    }
    else if(player_stats.hp <= 0 )
    {
        s_manager->sygnalize_to_pop();
        game_sys->stop_fight();
        game_sys->set_last_fight_status("lose");
    }
    for (auto &ptr : interface_elements)
    {
        ptr.get()->update();
    }
}

void Fight_state::enemy_turn()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distribution(1, 2);
    int randomNumber = distribution(rng);
    if (randomNumber == 1)
    {
        int some_value = (attack(turn::enemy) - defend(turn::player));
        player_stats.hp -= some_value;
    }
    else
    {
        int some_value = additional_defense(turn::enemy);
        enemy->add_hp(some_value);
    }
}

int Fight_state::attack(turn who)
{
    statistics to_use;
    if (who == turn::player)
    {
        to_use = player_stats;
    }
    else if (who == turn::enemy)
    {
        to_use = enemy->get_stats();
    }
    int attackDamage = (to_use.strength * 4) + (to_use.dexterity * 2) + (to_use.vitality * 2) + (to_use.charisma * 1);
    return attackDamage;
}

int Fight_state::spell(turn who)
{
    statistics to_use;
    if (who == turn::player)
    {
        to_use = player_stats;
    }
    else if (who == turn::enemy)
    {
        to_use = enemy->get_stats();
    }
    int spellDamage = (to_use.inteligence * 4) + (to_use.vitality * 1) + (to_use.charisma * 2);
    return spellDamage;
}

int Fight_state::defend(turn who)
{
    statistics to_use;
    if (who == turn::player)
    {
        to_use = player_stats;
    }
    else if (who == turn::enemy)
    {
        to_use = enemy->get_stats();
    }
    int defense = (to_use.vitality * 4) + (to_use.charisma * 2);
    return defense;
}

int Fight_state::additional_defense(turn who) // heal
{
    statistics to_use;
    if (who == turn::player)
    {
        to_use = player_stats;
    }
    else if (who == turn::enemy)
    {
        to_use = enemy->get_stats();
    }
    int defense = (to_use.vitality * 1) + (to_use.charisma * 1);
    return defense;
}

bool Fight_state::check_if_button_pressed()
{
    for (auto &button : buttons)
    {
        if (button->is_pressed())
        {
            action_to_be_performed = button->get_action_type();
            button->change_pressed();
            return true;
        }
    }
    return false;
}

std::unordered_map<std::string, std::string> Fight_state::change_to_map()
{
    statistics to_display = enemy->get_stats();
    std::unordered_map<std::string, std::string> text_to_display;
    text_to_display.insert({"name", "goblin"});
    text_to_display.insert({"defense", std::to_string(defend(turn::enemy))});
    text_to_display.insert({"attack damage", std::to_string(attack(turn::enemy))});
    text_to_display.insert({"hp", std::to_string(to_display.hp)});
    return text_to_display;
}

void Fight_state::handleinput(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos)
{
    for (auto &ptr : interface_elements)
    {
        ptr.get()->handle_input(event, window, mousepos);
    }
    for (auto&ptr: buttons)
    {
        ptr->handle_input(event, window, mousepos);
    }
}