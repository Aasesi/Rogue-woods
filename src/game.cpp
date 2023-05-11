#include "game.hpp"

Game::Game()
{
	initialize();
	statemanager = std::make_shared<State_manager>();
	statemanager->initialize();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return window->isOpen();
}

void Game::initialize()
{
	this->window = new sf::RenderWindow(sf::VideoMode(2200, 1400), "SFML Window", sf::Style::Default);
	this->window->setFramerateLimit(30);
}

void Game::run()
{
	while (running())
	{
		sf::Vector2f mousepos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		sf::Event event;
		while (window->pollEvent(event))
		{	
			if (event.type == sf::Event::Closed)
				this->window->close();
			// Pamietaj zeby zrobic by przekazywało przez referencje albo w sumie nie trzeba chyba
			statemanager->handleinput(event, *window, mousepos);

		}

		statemanager->update();
		window->clear();
		statemanager->render(*window);
		window->display();

	}
}
