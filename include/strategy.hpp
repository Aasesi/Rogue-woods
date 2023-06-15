#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include <string>
#include <vector>
#include "map.hpp"
#include "player_input.hpp"
#include "quest.hpp"
#include <player.hpp>

enum class Game_status
{
    Start,
    No_quests,
    Pop_up_quest,
    long_quest,
    Doing_quest
};

struct basic_informations
{
    // Neccessary objects
    Node* current_position;
    std::unique_ptr<Quest> main_quest = nullptr;
    std::unique_ptr<Quest> current_quest = nullptr;


    // Option text
    std::string text_to_display;
    std::set<std::string> possible_options;

    // Game neccessities
    Game_status status = Game_status::Start;
    double chance_of_spawning_quest = 0.2;

    // Player
    std::unique_ptr<Player> player = nullptr;
    
};

class Strategy
{
protected:
std::vector<std::string> string_of_options; // used for easy check of options może zrobić z tego funkcje
Node* changed_node;
public:
    Strategy(){};
    ~Strategy(){};

    virtual void process_information(std::string picked_option, basic_informations* informations) = 0;
    std::string get_options(std::set<std::string> opts);

    //virtual void map_movement() = 0;
    //virtual std::vector<std::string> current_option_update() = 0;
    //virtual void send_info_to_input(Player_input* player_in) = 0;
    //bool change_strategy();
};





#endif