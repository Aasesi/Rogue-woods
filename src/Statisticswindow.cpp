#include <Statisticswindow.hpp>

Statistics_window::Statistics_window(std::string path, sf::Vector2f position, std::string name, std::string species, statistics stats)
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

    text_to_display["name"] = name;
    text_to_display["species"] = species;
    text_to_display["hp"] = std::to_string(stats.hp);
    text_to_display["mana"] = std::to_string(stats.mana);
    text_to_display["strength"] = std::to_string(stats.strength);
    text_to_display["charisma"] = std::to_string(stats.charisma);
    text_to_display["inteligence"] = std::to_string(stats.inteligence);
    text_to_display["vitality"] = std::to_string(stats.vitality);
    text_to_display["dexterity"] = std::to_string(stats.dexterity);
}

Statistics_window::Statistics_window(std::string path, sf::Vector2f position, std::unordered_map<std::string, std::string> info_collection, statistics stats)
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
    text_to_display["species"] = info_collection["species"];
    text_to_display["fight class"] = info_collection["fight_class"];
    text_to_display["gold"] = info_collection["gold"];

    text_to_display["experience"] = std::to_string(stats.experience);
    text_to_display["level"] = std::to_string(stats.level);
    text_to_display["hp"] = std::to_string(stats.hp);
    text_to_display["mana"] = std::to_string(stats.mana);
    text_to_display["strength"] = std::to_string(stats.strength);
    text_to_display["charisma"] = std::to_string(stats.charisma);
    text_to_display["inteligence"] = std::to_string(stats.inteligence);
    text_to_display["vitality"] = std::to_string(stats.vitality);
    text_to_display["dexterity"] = std::to_string(stats.dexterity);
    text_to_display["gold"] = std::to_string(stats.gold);
}

void Statistics_window::handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos)
{
}
void Statistics_window::update()
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
void Statistics_window::render(sf::RenderWindow &window)
{
    window.draw(this->interface_sprite);
    window.draw(this->_text);
}

void Statistics_window::update_stats(statistics stats)
{
    text_to_display["hp"] = std::to_string(stats.hp);
    text_to_display["mana"] = std::to_string(stats.mana);
    text_to_display["strength"] = std::to_string(stats.strength);
    text_to_display["charisma"] = std::to_string(stats.charisma);
    text_to_display["inteligence"] = std::to_string(stats.inteligence);
    text_to_display["vitality"] = std::to_string(stats.vitality);
    text_to_display["dexterity"] = std::to_string(stats.dexterity);
    text_to_display["experience"] = std::to_string(stats.experience);
    text_to_display["gold"] = std::to_string(stats.gold);
    got_new_information = true;
}

void Statistics_window::update_name(std::string name)
{
    text_to_display["name"] = name;
}
