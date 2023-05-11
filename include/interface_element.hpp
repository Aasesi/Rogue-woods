#ifndef INTERFACE_ELEMENT_H_
#define INTERFACE_ELEMENT_H_

#include <string>
#include <SFML/Graphics.hpp>

class interface_element
{
protected:
    sf::Sprite interface_sprite;
    sf::Texture interface_texture;

public:
    interface_element() {};
    interface_element(std::string path, sf::Vector2f position)
    {
        this->interface_texture.loadFromFile(path);
        this->interface_sprite.setTexture(interface_texture);
        this->interface_sprite.setPosition(position);
    };
    virtual void render(sf::RenderWindow& window)
    {
        window.draw(this->interface_sprite);
    };
    virtual void update() = 0;
    virtual void handle_input(sf::Event& event, sf::RenderWindow& window, sf::Vector2f mousepos) = 0;
    virtual bool contains(sf::Vector2f point) const
    {
        return interface_sprite.getGlobalBounds().contains(point);
    };
};

#endif