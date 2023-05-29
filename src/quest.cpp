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
