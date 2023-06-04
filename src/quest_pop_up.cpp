#include <quest_pop_up.hpp>

Fast_quest::Fast_quest()
{

}

Fast_quest::Fast_quest(std::string name_of_the_file)
{
    all_options = std::move(my_utils::extract_text_for_quest(name_of_the_file));
    current_option = all_options[0].get();
}

Fast_quest::~Fast_quest()
{
    
}

void Fast_quest::next_option(std::string text)
{
    current_option = current_option->get_next_option(text);
}

std::set<std::string> Fast_quest::see_options()
{
    return current_option->get_possible_options();
}

