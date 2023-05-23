#ifndef OPTION_HPP_
#define OPTION_HPP_

#include <string>
class Node;

class Option
{
protected:
    std::string description;
    std::string direction_of_node;
    std::string name;
    std::pair<int, int> coordinates_of_next_node;
    Node *next_node = nullptr;
    bool has_next_node = false;

public:
    Option();
    Option(std::string desctrip, std::string directi, std::string name_, Node *node);
    ~Option(){};
    Node *get_next_node();
    std::string get_text() { return description; };
    std::string ret_dir() { return direction_of_node; };
    bool next_node_status() { return has_next_node; };
};

#endif