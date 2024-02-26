#ifndef QUEST_OPTION_HPP_
#define QUEST_OPTION_HPP_

#include "option.hpp"
#include <vector>
#include <set>
#include <memory>
#include <Item.hpp>

class Quest_option : public Option
{
private:
    Quest_option *parent_node;
    std::set<Quest_option *> sub_options;
    bool empty = true;
    bool has_item_reward = false;
    int exp_reward = 0;
    std::vector<std::string> item_reward;
    int gold_reward = 0;
    bool starts_battle = false;
    std::string enemy_type;

public:
    Quest_option();
    Quest_option(std::string desctrip, std::string directi, std::string name_, Quest_option *parent, bool is_empty);
    ~Quest_option();

    // Adding
    void add_sub_option(Quest_option *some_option);
    void assign_description(std::string text);
    void assign_directi(std::string text);
    void assign_exp_reward(int reward) { exp_reward = reward; };
    void assign_gold_reward(int amount) { gold_reward = amount; };
    void change_into_fight(){starts_battle = true;};
    void add_item_keyword(std::string s){item_reward.push_back(s);
    has_item_reward = true;};
    void assign_enemy_type(std::string enemy){enemy_type = enemy;};

    // Check functions
    bool is_parent_null();
    bool is_ending();
    bool has_fight() { return starts_battle; };
    bool has_item(){return has_item_reward;};

    // Get functions
    Quest_option *get_parent();
    std::set<std::string> get_possible_options();
    Quest_option *get_next_option(std::string some_text);
    int return_exp() { return exp_reward; };
    int return_gold() { return gold_reward; };
    std::vector<std::string> retrive_item(){return item_reward;};
    std::string get_enemy(){return enemy_type;};
};

#endif