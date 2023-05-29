#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include <string>
#include <vector>
#include "map.hpp"
#include "player_input.hpp"
#include "quest.hpp"

struct basic_informations
{
    // Pointers to neccessary
    Node* current_position;
    // tu bedzie trzeba zrobic pointera do opcji
    Option current_option;

    // Option text
    std::string text_to_display;
    std::set<std::string> possible_options; 
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

    //virtual void map_movement() = 0;
    //virtual std::vector<std::string> current_option_update() = 0;
    //virtual void send_info_to_input(Player_input* player_in) = 0;
    //bool change_strategy();
};





#endif