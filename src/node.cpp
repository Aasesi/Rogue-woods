#include "node.hpp"
#include "option.hpp"

void Node::add_option(Option some_option)
{
    {
        options.push_back(some_option);
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
    for (auto &option : options)
    {
        if (text == option.ret_dir())
        {
            return option.get_next_node();
        }
    }
    return nullptr;
}

std::string Node::display_options()
{
    // This function is going to return which node is next for picked option
    // Może da się to zrobić w check availibility funckcji by ustalic next noda i pozniej zwrocic

    std::string entire_text = "\n";
    for (auto &option : options)
    {
        entire_text += option.get_text() + "\n";
        current_options.push_back(option.ret_dir());
    }
    return entire_text;
}