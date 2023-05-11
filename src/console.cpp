#include "console.hpp"


void Console::handle_input(sf::Event& event, sf::RenderWindow& window, sf::Vector2f mousepos)
{
if (is_full && contains(mousepos))
	{
		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			{
				if (event.mouseWheelScroll.delta > 0)
				{
					dir = Up;
				}
				if (event.mouseWheelScroll.delta < 0)
				{
					dir = Down;
				}
			}
		}
	}
}