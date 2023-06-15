#include <player.hpp>

Player::Player(std::string name_, std::string species_, std::string fight_class_)
{
    name = name_;
    species = species_;
    fight_class = fight_class_;
    is_player = true;
}