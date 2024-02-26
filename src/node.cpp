#include "node.hpp"

Node::Node(std::string descript, std::string landmark, std::string region, std::string name_, int x, int y)
{
    Beginning_desription = descript;
    noteable_landmark = landmark;
    Region = region;
    name = name_;
    position = std::make_pair(x, y);
}

void Node::add_option(Option some_option)
{
    {
        basic_options.push_back(some_option);
    }
}

bool Node::check_availibility(std::string &some_text)
{
    for (const std::string &curr_option : current_options)
    {
        if (curr_option == some_text)
        {
            return true;
        }
    }
    return false;
}

Node *Node::next_node(std::string text)
{
    for (auto &option : basic_options)
    {
        if (text == option.ret_dir())
        {
            return option.get_next_node();
        }
    }
    return nullptr;
}


Option Node::get_option(std::string text)
{
    Option some_option;
    for (auto &option : basic_options)
    {
        if (text == option.ret_dir())
        {
            return option;
        }
    }
    return some_option;
}

std::set<std::string> Node::see_options()
{
    std::set<std::string> to_return;
    for (auto &option : basic_options)
    {
        to_return.insert(option.ret_dir());
    }
    return to_return;
}

bool Node::operator==(const Node &other)
{
    return position == other.position;
}

std::map<std::string, std::string> Node::information_to_return()
{
    std::map<std::string, std::string> to_return;
    to_return.insert({"Special name", name});
    to_return.insert({"Region", Region});
    to_return.insert({"Landmark", noteable_landmark});
    to_return.insert({"Position x", std::to_string(position.first)});
    to_return.insert({"Position y", std::to_string(position.second)});

    return to_return;
}