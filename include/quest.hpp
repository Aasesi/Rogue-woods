#ifndef QUEST_HPP_
#define QUEST_HPP_

#include "quest_option.hpp"
#include "utils.hpp"
#include "console.hpp"


class Quest
{
private:
std::vector<std::unique_ptr<Quest_option>> all_options;
Quest_option* current_option = nullptr;
public:
    // Constructors
    Quest();
    Quest(std::string name_of_the_file);
    ~Quest();


    // Managing options
    void push_option(std::unique_ptr<Quest_option> some_option);

    // Game functions
    std::vector<std::string> Start(Console* console);
    std::pair<int, Node*> update(std::string text);

};

#endif