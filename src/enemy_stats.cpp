#include "enemy_stats.hpp"

Enemy_stats::Enemy_stats(std::string path, sf::Vector2f position, std::unordered_map<std::string, std::string> info_collection)
{
    this->interface_texture.loadFromFile(path);
    this->interface_sprite.setTexture(interface_texture);
    this->interface_sprite.setPosition(position);
    if (!_font.loadFromFile(font_path))
    {
    }
    _text.setFont(_font);
    _text.setCharacterSize(16);
    _text.setPosition(sf::Vector2f(position.x + 20, position.y + 20));
    text_to_display["name"] = info_collection["name"];
    text_to_display["defense"] = info_collection["defense"];
    text_to_display["attack damage"] = info_collection["attack damage"];
    text_to_display["hp"] = info_collection["hp"];
}

Enemy_stats::~Enemy_stats()
{
}

void Enemy_stats::handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos)
{
}

void Enemy_stats::update()
{
    if (got_new_information)
    {
        entire_string = "";
        for (const auto &values : text_to_display)
        {
            entire_string += values.first + ": " + values.second + "\n" + "\n";
        }
        got_new_information = false;
        _text.setString(entire_string);
    }
    
}

void Enemy_stats::render(sf::RenderWindow &window)
{
    window.draw(this->interface_sprite);
    window.draw(this->_text);
}

void Enemy_stats::update_stats(std::unordered_map<std::string, std::string> info_collection)
{
    text_to_display["name"] = info_collection["name"];
    text_to_display["defense"] = info_collection["defense"];
    text_to_display["attack damage"] = info_collection["attack damage"];
    text_to_display["hp"] = info_collection["hp"];
    got_new_information = true;
}