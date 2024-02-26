#include <inv_quest.hpp>


Inv_menu::Inv_menu()
{
    Option first_option("You open your inventory", "inventory", "inventory menu", nullptr);
    options.push_back(first_option);
    
}

Inv_menu::~Inv_menu()
{
    
}

void Inv_menu::next_option(std::string next_opt)
{
    
}
