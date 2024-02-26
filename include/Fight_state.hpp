#ifndef FIGHT_STATE
#define FIGHT_STATE

#include <state.hpp>
#include <string>
#include <character.hpp>
#include <game_system.hpp>
#include <action_button.hpp>
#include <enemy_stats.hpp>
#include <enemy.hpp>
#include <random>

enum class turn
{
    player,
    enemy
};

class Fight_state : public State
{
public:
    Fight_state();
    Fight_state(const std::string path, Game_system * game_sys_);
    ~Fight_state();
    void render(sf::RenderWindow &window) override;
    void update() override;
    int attack(turn who);
    int spell(turn who);
    int defend(turn who);
    int additional_defense(turn who);
    bool check_if_button_pressed();
    void enemy_turn();
    std::unordered_map<std::string, std::string> change_to_map();
    void handleinput(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos) override;
private:
    Game_system *game_sys;
    statistics player_stats;
    std::unique_ptr<Enemy> enemy = nullptr;
    sf::Texture enemy_texture;
    sf::Sprite enemy_sprite;
    std::vector<std::unique_ptr<action_button>> buttons;
    action_type action_to_be_performed = action_type::None;
    turn whose = turn::player;
    Enemy_stats* e_s = nullptr;

};

#endif