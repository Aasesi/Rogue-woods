#include "button.hpp"

Button::Button(const std::string path, sf::Vector2f position, type_of_button button_t, std::shared_ptr<State_manager> s_m)
{
    this->interface_texture.loadFromFile(path);
    this->interface_sprite.setTexture(interface_texture);
    this->interface_sprite.setPosition(position);
    button_type = button_t;
    state_m = s_m;
}

void Button::handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos)
{
    switch (button_type)
    {
    case type_of_button::Play_button:
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && contains(mousepos))
        {
            std::unique_ptr<Game_state> game = std::make_unique<Game_state>(game_background);
            game->setManager(state_m);
            state_m->push(std::move(game));
        }
        break;
    case type_of_button::Exit_button:
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && contains(mousepos))
        {
            window.close();
        }
    default:
        break;
    }
}

void Button::update()
{

}