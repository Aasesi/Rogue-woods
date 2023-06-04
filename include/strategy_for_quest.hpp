#ifndef STRATEGY_FOR_QUEST_HPP_
#define STRATEGY_FOR_QUEST_HPP_

#include <strategy.hpp>

class Quest_strategy : public Strategy
{
private:
public:
    void process_information(std::string picked_option, basic_informations *informations) override;
};

#endif