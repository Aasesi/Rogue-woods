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
    if (!doing_quest)
    {
        for (auto &option : basic_options)
        {
            if (text == option.ret_dir())
            {
                return option.get_next_node();
            }
        }
    }
    else
    {
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

void Node::reset_current_options()
{
    current_options.clear();
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
std::pair<int, Node*> Node::update_quest_position(std::string text)
{
    std::pair<int, Node*> option_choice = quests.back()->update(text);
    if (option_choice.first == 2)
    {
        doing_quest = false;
        quests.pop_back();
        return option_choice;
    }
    else if (option_choice.first == 1)
    {
        return option_choice;
    }
    else
    {
        // Wazne nie zmieniaj pzycji w ostatniej opcji bo moga byc problemy
        doing_quest = false;
        action_done = true;
        quests.pop_back();
        return option_choice;
    }
    
}