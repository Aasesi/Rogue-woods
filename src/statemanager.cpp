#include "statemanager.hpp"
#include "state.hpp"
#include "button.hpp"

State_manager::State_manager()
{

}

State_manager::~State_manager()
{
	
}

void State_manager::push(std::unique_ptr<State> state)
{
	states.push(std::move(state));
}

void State_manager::initialize()
{
	std::unique_ptr<State> menu = std::make_unique<State>(main_menu_path);
	menu.get()->add_interface_element(std::make_shared<Button>(play_button_path, sf::Vector2f(925.f, 200.f), type_of_button::Play_button, std::shared_ptr<State_manager>(this)));
	menu.get()->add_interface_element(std::make_shared<Button>(exit_button_path, sf::Vector2f(925.f, 670.f), type_of_button::Exit_button, std::shared_ptr<State_manager>(this)));
	push(std::move(menu));
	empty = false;
}

void State_manager::pop()
{
	if (empty == false)
		states.pop();
	else
		std::cout << "There aren't any states inside the stack." << "\n";
}

void State_manager::handleinput(sf::Event& event, sf::RenderWindow& window, sf::Vector2f mousepos)
{
	states.top()->handleinput(event, window, mousepos);
}


void State_manager::render(sf::RenderWindow& window)
{
	states.top()->render(window);
}

void State_manager::update()
{
	states.top()->update();
}

