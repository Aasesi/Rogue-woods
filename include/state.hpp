#ifndef STATE_H_
#define STATE_H_

#include "interface_element.hpp"
#include "statemanager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>


class State
{
public:
	State() {};
	State(const std::string path) 
	{
		this->background_texture.loadFromFile(path);
        this->background_sprite.setTexture(background_texture);
        this->background_sprite.setPosition( sf::Vector2f(0, 0));
	};
	~State() {};
	virtual void update()
	{
		for(auto& ptr: interface_elements)
		{
			ptr.get()->update();
		}
	};
	virtual void render(sf::RenderWindow& window)
	{
		window.draw(this->background_sprite);
		for(auto& ptr: interface_elements)
		{
			ptr.get()->render(window);
		}
	};
	virtual void handleinput(sf::Event &event, sf::RenderWindow& window, sf::Vector2f mousepos)
	{
		for(auto& ptr: interface_elements)
		{
			ptr.get()->handle_input(event, window, mousepos);
		}
	};
	void setManager(std::shared_ptr<State_manager> manager) {
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