#ifndef QUEST_HPP_
#define QUEST_HPP_

#include "quest_option.hpp"
#include "utils.hpp"
#include "console.hpp"
#include <set>

class Quest
{
protected:
    std::vector<std::unique_ptr<Quest_option>> all_options;
    Quest_option *current_option = nullptr;
public:
    // Constructors
    Quest();
    Quest(std::string name_of_the_file);
    ~Quest();

    // Managing options
    void push_option(std::unique_ptr<Quest_option> some_option);
    std::string get_description() { return current_option->get_text(); };
    bool check_if_ends() {return current_option->is_ending();};
    virtual void next_option(std::string text) = 0;
    virtual std::set<std::string> see_options() = 0;
};

#endif