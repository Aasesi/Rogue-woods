#ifndef OPTION_HPP_
#define OPTION_HPP_

#include <string>
#include "node.hpp"

class Option
{
private:
    std::string description;
    std::string direction_of_node;
    std::string name;
    Node *next_node = nullptr;

public:
    Option(){};
    Option(std::string desctrip, std::string directi, std::string name_, Node *node)
    {
        description = desctrip;
        direction_of_node = directi;
        name = name_;
        next_node = node;
    };
    ~Option(){};
    Node *get_next_node();
    std::string get_text() { return description; };
    std::string ret_dir() { return direction_of_node; };
};

#endif