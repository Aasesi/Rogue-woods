#ifndef DEFAULT_STRATEGY_HPP_
#define DEFAULT_STRATEGY_HPP_

#include "strategy.hpp"
#include "player_input.hpp"
#include <string>

class Default_strategy : public Strategy
{
public:
    void process_information(std::string picked_option, basic_informations *informations) override;
};

#endif