#include <mapstats.hpp>

Map_stats::Map_stats(std::string path, sf::Vector2f position, std::map<std::string, std::string> some_info)
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

    info_to_show = some_info;
}

void Map_stats::update()
{
    if (updated)
    {
        updated = false;
        entire_string = "";
        for (const auto &info : info_to_show)
        {
            if (info.second == "")
            {
                continue;
            }
            entire_string += info.first + ": " + info.second + "\n";
        }
        _text.setString(entire_string);
    }
}

void Map_stats::handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos)
{
}

void Map_stats::render(sf::RenderWindow &window)
{
    window.draw(this->interface_sprite);
    window.draw(this->_text);
}

void Map_stats::new_entire_info(std::map<std::string, std::string> info)
{
    updated = true;
    info_to_show = info;
};