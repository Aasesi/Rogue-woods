#include "option.hpp"
#include "node.hpp"

Option::Option()
{
    description = "";
    name = "";
    direction_of_node = "";
}

Option::Option(std::string desctrip, std::string directi, std::string name_, Node *node)
{
    description = desctrip;
    direction_of_node = directi;
    name = name_;
    next_node = node;
}

Node *Option::get_next_node()
{
    return next_node;
}