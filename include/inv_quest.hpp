#ifndef INV_QUEST_HPP_
#define INV_QUEST_HPP_

#include <string>
#include <set>
#include <vector>
#include "option.hpp"

class Inv_menu
{
private:
std::vector<Option> options;
public:
    Inv_menu();
    ~Inv_menu();
    void next_option(std::string text);
};

#endif