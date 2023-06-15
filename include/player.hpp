#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <character.hpp>

class Player : public Character
{
public:
    Player(std::string name_, std::string species_, std::string fight_class_);
    statistics get_stats() { return stats; };

private:
};

#endif