#ifndef GAME_SYSTEM_HPP_
#define GAME_SYSTEM_HPP_

#include "node.hpp"
#include "player.hpp"
#include "quest.hpp"
#include "console.hpp"
#include "quest_pop_up.hpp"
#include <random>
#include "player_input.hpp"
#include "Statisticswindow.hpp"
#include "mapstats.hpp"
#include "map.hpp"
#include "option.hpp"
#include "statemanager.hpp"
#include "enemy.hpp"

enum class Game_status
{
    Start,
    No_quests,
    Pop_up_quest,
    long_quest,
    Doing_quest,
    End_of_quest,
    Inventory
};

class Game_system
{
public:
    Game_system();
    Game_system(std::string name_of_player, std::string species, std::string player_class, Node *some_node, std::shared_ptr<State_manager> state_mana);
    ~Game_system();
    void quest_next_move(std::string move_text);
    void go_to_next_node(std::string move_text);
    void add_text_to_console(Console *console);
    void add_specific_text_to_console(Console *console, std::string text_to_add);
    void generate_fast_quest();
    int generate_random_num(int range);
    void get_text_to_display();
    std::string get_options(std::set<std::string> opts);
    void change_game_status(Game_status new_status)
    {
        previous_status = status;
        status = new_status;
    };
    void update_player_input_options(Player_input *player_input);
    void update_interface_elements(Map *mapa, Map_stats *map_stats, Statistics_window *stat_window);
    void add_reward();
    Game_status get_status() { return status; };
    void set_special_option(std::string s) { special_option = s; };
    bool fight_start() { return start_fight; };
    void stop_fight(){start_fight = false;};
    std::string get_enemy_type() { return current_quest->get_enemy_type(); };
    statistics get_player_stats(){return player->get_stats();};
    void set_last_fight_status(std::string s){last_fight_status = s; had_fight = true;};
    bool had_fight_s(){return had_fight;};
    std::string return_last_fight(){return last_fight_status;};
    void change_something(){had_fight = false;};
private:
    Node *current_position = nullptr;
    Game_status status = Game_status::Start;
    Game_status previous_status;
    double chance_of_spawning_quest = 0.8;
    std::string last_fight_status = "lose";
    bool start_fight = false;
    bool had_fight = false;

    // Player
    std::unique_ptr<Player> player = nullptr;

    std::unique_ptr<Quest> current_quest = nullptr;
    std::vector<std::unique_ptr<Quest>> quests;

    std::string special_option;

    std::string text_to_display;
    std::set<std::string> possible_options;

    std::vector<std::string> quest_names = {"The_lost_ring_quest.txt"};
    std::unique_ptr<Quest> inv_menu = nullptr;

    std::shared_ptr<State_manager> state_manager = nullptr;
};

#endif