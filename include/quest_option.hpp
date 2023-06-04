#ifndef QUEST_OPTION_HPP_
#define QUEST_OPTION_HPP_

#include "option.hpp"
#include <vector>
#include <set>

class Quest_option : public Option
{
private:
    Quest_option *parent_node;
    std::set<Quest_option *> sub_options;
    bool empty = true;
public:
    Quest_option();
    Quest_option(std::string desctrip, std::string directi, std::string name_, Quest_option *parent, bool is_empty);
    ~Quest_option();

    // Adding
    void add_sub_option(Quest_option *some_option);
    void assign_description(std::string text);
    void assign_directi(std::string text);

    // Check functions
    bool is_parent_null();
    bool is_ending();

    // Get functions
    Quest_option *get_parent();
    std::set<std::string> get_possible_options();
    Quest_option* get_next_option(std::string some_text);
};

#endif