#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include "character.hpp"

class Enemy:public Character
{
public:
Enemy(){};
Enemy(std::string name_, statistics stats_){name = name_; stats = stats_;};
~Enemy(){};
std::string get_name(){return name;};
statistics get_stats(){return stats;};
private:


};


#endif