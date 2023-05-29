#include "quest_menu.hpp"

Quest_menu::Quest_menu()
{

}


Quest_menu::~Quest_menu()
{

}


Game_status Quest_menu::get_status()
{
    if(status == Game_status::Start)
    {
        status = Game_status::No_quests;
        return Game_status::Start;
    }
    return status;
}