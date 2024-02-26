#ifndef STATE_H_
#define STATE_H_

#include "interface_element.hpp"
#include "statemanager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <thread>
#include <ranges>

class State
{
public:
	State(){};
	State(const std::string path)
	{
		this->background_texture.loadFromFile(path);
		this->background_sprite.setTexture(background_texture);
		this->background_sprite.setPosition(sf::Vector2f(0, 0));
	};
	~State(){};
	virtual void update()
	{
		std::vector<std::thread> threads;
		for (auto &ptr : interface_elements)
		{
			threads.emplace_back([&ptr]()
								 { ptr->update(); });
		}

		std::for_each(threads.begin(), threads.end(), [](std::thread &t)
					  { t.join(); });
	};
	virtual void render(sf::RenderWindow &window)
	{
		window.draw(this->background_sprite);

		std::ranges::for_each(interface_elements, [&window](auto &ptr)
							  { ptr->render(window); });
	};
	virtual void handleinput(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos)
	{

		std::vector<std::thread> threads;
		for (auto &ptr : interface_elements)
		{
			threads.emplace_back([&ptr, &event, &window, &mousepos]()
								 { ptr->handle_input(event, window, mousepos); });
		}

		std::for_each(threads.begin(), threads.end(), [](std::thread &t)
					  { t.join(); });
	};
	void setManager(std::shared_ptr<State_manager> manager)
	{
		s_manager = manager;
		is_manager_null = false;
	}
	virtual void add_interface_element(std::unique_ptr<interface_element> element)
	{
		interface_elements.push_back(std::move(element));
	};

protected:
	std::shared_ptr<State_manager> s_manager = nullptr;
	bool is_manager_null = true;
	std::vector<std::unique_ptr<interface_element>> interface_elements;
	sf::Sprite background_sprite;
	sf::Texture background_texture;
};

#endif