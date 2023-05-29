#include "node.hpp"

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

std::string Node::display_basic_options()
{
    // This function is going to return which node is next for picked option
    // Może da się to zrobić w check availibility funckcji by ustalic next noda i pozniej zwrocic

    std::string entire_text = "\n";
    for (auto &option : basic_options)
    {
        entire_text += option.get_text() + "\n";
        current_options.insert(option.ret_dir());
    }
    return entire_text;
}

std::string Node::display_quest_options(const std::vector<std::string> &vec)
{
    std::string entire_text = "\n*After resting it is time to decide where to go*\n";
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        entire_text += vec[i] + "\n";
        current_options.insert(vec[i]);
    }
    return entire_text;
}

// ważne moglbym zrobic pare basic options i po prostu dodawac pointera z map ktora by miala vectora z unique pointerami do opcji !!!
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