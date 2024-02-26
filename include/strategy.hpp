#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include <string>
#include <vector>
#include "map.hpp"
#include "player_input.hpp"
#include "quest.hpp"
#include <player.hpp>
#include <game_system.hpp>


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
    double chance_of_spawning_quest = 0.8;

    // Player
    std::unique_ptr<Player> player = nullptr;
};

class Strategy
{
protected:
std::vector<std::string> string_of_options; 
Node* changed_node;
public:
    Strategy(){};
    ~Strategy(){};

    virtual void process_information(std::string picked_option, basic_informations* informations) = 0;
    virtual void process_information(Game_system* game_sys, std::string picked_option) = 0;
    std::string get_options(std::set<std::string> opts);
};





#endif