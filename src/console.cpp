#include "console.hpp"

// 57 to maks słów
Console::Console(std::string path, sf::Vector2f position)
{
	this->interface_texture.loadFromFile(path);
	this->interface_sprite.setTexture(interface_texture);
	this->interface_sprite.setPosition(position);
	if (!_font.loadFromFile(font_path))
	{
	}
	_text.setFont(_font);
	_text.setCharacterSize(16);
	_text.setString("hELLO");
	_text.setPosition(sf::Vector2f(460.f, 150.f));
	_text.setFillColor(sf::Color::White);

	dir = None;
}

void Console::handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos)
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

void Console::get_focus()
{
	if (is_full)
	{
		int some_size = down_lines.size();
		for (int i = 0; i < some_size; i++)
		{
			console_text += down_lines.back();
			down_lines.pop_back();
			size_t target_pos = console_text.find("\n") + 1;
			std::string new_line = console_text.substr(0, target_pos);
			console_text.erase(0, target_pos);
			up_lines.push_back(new_line);
		}
	}
}

void Console::add_new_text(std::string new_text)
{
	if (!new_text.empty())
	{
		const std::string character = "\n";
		int substringcount = std::count_if(new_text.begin(), new_text.end(), [character](char c)
										   { return c == character[0]; });
		curr_lines += substringcount;

		if (curr_lines >= number_of_lines && !is_scrolled())
		{
			console_text += new_text;
			is_full = true;
			for (int i = 0; i < substringcount; i++)
			{
				size_t target_pos = console_text.find("\n");
				std::string new_line = console_text.substr(0, target_pos + 1);
				console_text.erase(0, target_pos + 1);
				up_lines.push_back(new_line);
				curr_lines--;
			}
			_text.setString(console_text);
		}
		else if (curr_lines >= number_of_lines && is_scrolled())
		{
			is_full = true;
			get_focus();
			console_text += new_text;
			for (int i = 0; i < substringcount; i++)
			{
				size_t target_pos = console_text.find("\n");
				std::string new_line = console_text.substr(0, target_pos + 1);
				console_text.erase(0, target_pos + 1);
				up_lines.push_back(new_line);
				curr_lines--;
			}
			_text.setString(console_text);
		}
		else
		{
			console_text += new_text;
			_text.setString(console_text);
		}
	}
	else
	{
	}
}

bool Console::is_scrolled()
{
	if (down_lines.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Console::render(sf::RenderWindow &window)
{
	window.draw(this->interface_sprite);
	window.draw(this->_text);
}