#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <character.hpp>

class Player : public Character
{
public:
    Player(std::string name_, std::string species_, std::string fight_class_);
    statistics get_stats() { return stats; };
    std::unordered_map<std::string, std::string> collect_player_info();
    void leveling_up();
    void add_experience(int additional_exp);
    void add_gold(int amount);
    void add_item_ton_inv(std::unique_ptr<Item> some_item);
    std::vector<std::string> Item_info();
    bool put_item_as_weapon(std::string weapon);
    bool put_item_as_armor(std::string armor);

private:
    std::vector<std::unique_ptr<Item>> inventory;
    int max_inv_space = 6;
    int gold = 0;
    Item *current_weapon = nullptr;
    Item *current_armor = nullptr;
};

#endif