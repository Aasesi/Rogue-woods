#include <game_system.hpp>

Game_system::Game_system()
{
}

Game_system::Game_system(std::string name_of_player, std::string species, std::string player_class, Node *some_node, std::shared_ptr<State_manager> state_mana)
{
    player = std::make_unique<Player>("Your name", "Human", "Adventurer");
    current_position = some_node;
    state_manager= state_mana;

}

Game_system::~Game_system()
{
}

void Game_system::go_to_next_node(std::string move_text)
{
    current_position = current_position->next_node(move_text);
}

void Game_system::quest_next_move(std::string move_text)
{
    current_quest->next_option(move_text);
    if (current_quest->check_if_ends())
    {
        status = Game_status::End_of_quest;
        add_reward();
        if (current_quest->check_for_item())
        {
            std::vector<std::string> item_specs = current_quest->get_item_info();
        }
    }
}

void Game_system::add_reward()
{
    player->add_experience(current_quest->get_exp());
}

void Game_system::add_specific_text_to_console(Console *console, std::string text_to_add)
{
    console->add_new_text(text_to_add);
}

void Game_system::add_text_to_console(Console *console)
{
    console->add_new_text(text_to_display);
}

void Game_system::generate_fast_quest()
{
    current_quest = std::make_unique<Fast_quest>(quest_names[0]);
    status = Game_status::Pop_up_quest;
    possible_options = current_quest->see_options();
    text_to_display = current_quest->get_description();
}

int Game_system::generate_random_num(int range)
{
    std::mt19937 mt(std::time(0));
    std::uniform_int_distribution<int> dist(0, range);
    int randomNumber = dist(mt);
    return randomNumber;
}

std::string Game_system::get_options(std::set<std::string> opts)
{
    std::string whole_string;
    for (const auto &opt : opts)
    {
        whole_string += "<" + opt + ">\n";
    }
    return whole_string;
}

void Game_system::get_text_to_display()
{
    if (status == Game_status::No_quests || status == Game_status::Start)
    {
        possible_options = current_position->see_options();
        text_to_display = current_position->Display_begin_description();
        text_to_display += get_options(possible_options);
        if (status == Game_status::Start)
        {
            status = Game_status::No_quests;
        }
    }
    else if (status == Game_status::Pop_up_quest)
    {
        text_to_display = current_quest->get_description();
        possible_options = current_quest->see_options();
        text_to_display += get_options(possible_options);
        if(current_quest->has_fight())
        {
            start_fight = true;
        }
    }
    else if (status == Game_status::End_of_quest)
    {
        text_to_display = current_quest->get_description();
        possible_options = current_position->see_options();
        text_to_display += "\n" + current_position->Display_begin_description();
        text_to_display += get_options(possible_options);
        status = Game_status::No_quests;
    }
}

void Game_system::update_player_input_options(Player_input *player_input)
{
    player_input->update_options(possible_options);
}

void Game_system::update_interface_elements(Map *mapa, Map_stats *map_stats, Statistics_window *stat_window)
{
    std::pair<unsigned int, unsigned int> coords = current_position->get_coordinates();
    mapa->change_coordinates(coords.first, coords.second);
    map_stats->new_entire_info(current_position->information_to_return());
    stat_window->update_stats(player->get_stats());
}

