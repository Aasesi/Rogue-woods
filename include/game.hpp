#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "statemanager.hpp"

class Game
{
private:
	void initialize();
    sf::RenderWindow* window;
	std::shared_ptr<State_manager> statemanager;
public:
	Game();
	~Game();
	const bool running()const;
	void run();
};

#endif