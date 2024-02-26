#ifndef DEFAULT_STRATEGY_HPP_
#define DEFAULT_STRATEGY_HPP_

#include "strategy.hpp"
#include "player_input.hpp"
#include <quest_pop_up.hpp>
#include <string>
#include <random>

class Default_strategy : public Strategy
{
public:
    void process_information(std::string picked_option, basic_informations *informations) override;
    void process_information(Game_system* game_system, std::string picked_option) override;
    bool check_chance(double chance);
};

#endif