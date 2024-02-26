#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <string>
#include <unordered_map>
#include<utils.hpp>

class Character
{
public:
    Character(){};
    ~Character(){};
    void change_hp(int change){stats.hp -= change;};
void add_hp(int change){stats.hp += change;};
protected:
    std::string name;
    std::string species;
    std::string fight_class;
    statistics stats;

    bool is_player = false;
};

#endif