#include "action_button.hpp"

action_button::action_button()
{
}

action_button::action_button(std::string path, sf::Vector2f position, action_type type_of_button_)
{
    this->interface_texture.loadFromFile(path);
    this->interface_sprite.setTexture(interface_texture);
    this->interface_sprite.setPosition(position);
    action_performed = type_of_button_;
}
action_button::~action_button()
{
}
void action_button::handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && contains(mousepos))
    {
        std::cout<<"pressed";
        pressed = true;
    }
}
void action_button::update()
{
}