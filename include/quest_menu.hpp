#ifndef QUEST_MENU_HPP_
#define QUEST_MENU_HPP

#include "interface_element.hpp"
#include <vector>
#include "quest.hpp"

enum class Game_status
{
    Start,
    No_quests,
    Pop_up_quest,
    long_quest,
    Doing_quest
};

class Quest_menu
{
private:
std::unique_ptr<Quest> pop_up_quest = nullptr;
Quest* current_long_quest = nullptr;
std::vector<std::unique_ptr<Quest>> long_quests;
Game_status status = Game_status::Start;

// Generating chance
double chance_of_creating_quest = 0.6;

public:
// Constructors
Quest_menu();
~Quest_menu();

// Quest managing functions
void update_quest();
Quest* get_quest();

// Game mechanics connected functions
void update();
void generate_random_quest();
Game_status get_status();


};

#endif