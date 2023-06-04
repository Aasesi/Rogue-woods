#ifndef QUEST_POP_UP_HPP_
#define QUEST_POP_UP_HPP_

#include <quest.hpp>

class Fast_quest : public Quest
{
private:
public:
    Fast_quest();
    Fast_quest(std::string name_of_the_file);
    ~Fast_quest();
    void next_option(std::string text) override;
    std::set<std::string> see_options() override;
};

#endif