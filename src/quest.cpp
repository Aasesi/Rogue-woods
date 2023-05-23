#include "quest.hpp"

Quest::Quest()
{
}

Quest::Quest(std::string name_of_the_file)
{
    all_options = std::move(my_utils::extract_text_for_quest(name_of_the_file));
}

Quest::~Quest()
{
}

void Quest::push_option(std::unique_ptr<Quest_option> some_option)
{
    all_options.push_back(std::move(some_option));
}

std::vector<std::string> Quest::Start(Console *console)
{
    current_option = all_options[0].get();
    console->add_new_text(current_option->get_text());
    std::vector<std::string> options_in_string_vec = current_option->get_possible_options();
    return options_in_string_vec;
}

std::pair<int, Node*> Quest::update(std::string text)
{
    // nie zrobilem jeszcze koordynatow
    if(current_option->get_next_option(text)->next_node_status())   // W quest option moge zrobic bool czy ma nullptr jako next noda
    {
        current_option = current_option->get_next_option(text);
        return std::make_pair(2, current_option->get_next_node());
    }
    if (!current_option->is_ending())
    {
        current_option = current_option->get_next_option(text);  // Return 1 if next option nothing happens
        return std::make_pair(1, nullptr);
    }
    else
    { 
        return std::make_pair(0, nullptr);    // Return  if it is ending option
    }
}