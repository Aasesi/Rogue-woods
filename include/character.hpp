#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <string>
#include <unordered_map>

struct statistics
{
    int hp = 100;
    int mana = 100;

    int inteligence = 1;
    int strength = 1;
    int dexterity = 1;
    int vitality = 1;
    int charisma = 1;
};

class Character
{
public:
    Character(){};
    ~Character(){};
protected:
    std::string name;
    std::string species;
    std::string fight_class;
    statistics stats;

    bool is_player = false;
};

#endif