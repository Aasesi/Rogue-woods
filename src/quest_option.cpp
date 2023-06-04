#include "quest_option.hpp"

Quest_option::Quest_option(std::string desctrip, std::string directi, std::string name_, Quest_option *parent, bool is_empty)
{
    description = desctrip;
    direction_of_node = directi;
    name = name_;
    parent_node = parent;
    empty = is_empty;
}

Quest_option::Quest_option()
{
    name = "";
    description = "";
    direction_of_node = "";
    parent_node = nullptr;
}

Quest_option::~Quest_option()
{
}

/**
 * Assigning text
 */

void Quest_option::add_sub_option(Quest_option *some_option)
{
    sub_options.insert(some_option);
}

void Quest_option::assign_description(std::string text)
{
    description = text;
}

void Quest_option::assign_directi(std::string text)
{
    direction_of_node = text;
}

// Checking
bool Quest_option::is_parent_null()
{
    return (parent_node == nullptr) ? true : false;
}

// Get functions
Quest_option *Quest_option::get_parent()
{
    return parent_node;
}

std::set<std::string> Quest_option::get_possible_options()
{
    std::set<std::string> to_return;
    for (auto &sub_opt : sub_options)
    {
        to_return.insert(sub_opt->ret_dir());
    }
    return to_return;
}

Quest_option *Quest_option::get_next_option(std::string some_text)
{
    for (auto &sub_opt : sub_options)
    {
        if (some_text == sub_opt->ret_dir())
        {
            return sub_opt;
        }
    }
    return nullptr;
}

bool Quest_option::is_ending()
{
    return sub_options.empty();
}