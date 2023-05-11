#include "console.hpp"

Console::Console()
{
	if (!_font.loadFromFile(font_path))
	{
		
	}
	_text.setFont(_font);
	_text.setCharacterSize(24);
	_text.setPosition(sf::Vector2f(95.f, 200.f));
	_text.setFillColor(sf::Color::White);

	dir=None;
}

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

void Console::update()
{
	if (dir == Up && !up_lines.empty())
	{
		std::string new_text = up_lines.back() + console_text;
		up_lines.pop_back();

		// Code looks for the second last iteration of "\n" symbol by first searching for the last and then for second last
		size_t pos_wrong = new_text.find_last_of("\n");
		size_t pos_right = new_text.substr(0, pos_wrong).find_last_of("\n") + 1;

		std::string last_line_text = new_text.substr(pos_right);
		new_text.erase(pos_right);
		down_lines.push_back(last_line_text);
		console_text = new_text;
		_text.setString(console_text);
		dir = None;
	}
	else if (dir == Down && !down_lines.empty())
	{
		console_text += down_lines.back();
		down_lines.pop_back();
		size_t previous_first_line = console_text.find("\n") + 1;
		std::string new_line = console_text.substr(0, previous_first_line);
		up_lines.push_back(new_line);
		console_text.erase(0, previous_first_line);
		_text.setString(console_text);
		dir = None;
	}
	else
	{
		dir = None;
	}
}