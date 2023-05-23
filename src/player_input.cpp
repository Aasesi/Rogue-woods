#include "player_input.hpp"

// Tu może być coś źle z ptr
Player_input::Player_input(std::string path, sf::Vector2f position, Console*console_ptr, Map* map_ptr)
{
    this->interface_texture.loadFromFile(path);
    this->interface_sprite.setTexture(interface_texture);
    this->interface_sprite.setPosition(position);
    console = console_ptr;
    map = map_ptr;
    if (!_font.loadFromFile(font_path))
    {
    }
    _text.setFont(_font);
    _text.setCharacterSize(20);
    _text.setString(default_string);
    _text.setPosition(sf::Vector2f(1370.f, 1190.f));
    _text.setFillColor(sf::Color::Black);
}

// Moge dodac gdy ESC zeby wyjsc
void Player_input::update()
{
    // When writing text
    if (clicked)
    {
        _text.setString(input_text);
    }
    // When player pressed enter
    else if (sending_message)
    {
        if(check_option_availibility(input_text))
        {
            map->update_position(input_text);
            input_text = "\n<After contemplating you decided to: " + input_text + ">" + "\n\n";
            _text.setString(default_string);
			console->add_new_text(input_text);
			input_text.erase();
			sending_message = false;
        }
        else
        {
            _text.setString(default_string);
			console->add_new_text("\nIncorrect decision\n");
			input_text.erase();
			sending_message = false;
        }
    }
}

void Player_input::handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos)
{
    if (contains(mousepos) || clicked == true)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            clicked = true;
            _text.setString(" ");
        }
        if (clicked && event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode == '\b' && !input_text.empty())
            {
                input_text.pop_back();
            }
            if (event.text.unicode == '\r')
            {
                clicked = false;
                sending_message = true;
            }
            else if (event.text.unicode >= 32 && event.text.unicode <= 126)
            {
                input_text += static_cast<char>(event.text.unicode);
            }
        }
    }
}

void Player_input::render(sf::RenderWindow &window)
{
    window.draw(this->interface_sprite);
    window.draw(this->_text);
}

bool Player_input::check_option_availibility(std::string& text)
{
    return map->get_current_node()->check_availibility(text);
}