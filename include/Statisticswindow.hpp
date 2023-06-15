#ifndef STATISTICSWINDOW_HPP_
#define STATISTICSWINDOW_HPP_

#include "interface_element.hpp"
#include "character.hpp"
#include "configs.hpp"
#include "unordered_map"

class Statistics_window : public interface_element
{
public:
    Statistics_window(std::string path, sf::Vector2f position, std::string name, std::string species, statistics stats);
    void handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    void update_stats(statistics stats);
    void update_species(std::string species);
    void update_name(std::string name);

private:
    std::unordered_map<std::string, std::string> text_to_display = {{"vitality", ""}, {"charisma", ""}, {"dexterity", ""}, {"strength", ""}, {"inteligence", ""}, {"mana", ""}, {"hp", ""}, {"name", ""}, {"species", ""}};
    std::string entire_string = "";
    sf::Text _text;
    sf::Font _font;
    bool got_new_information = true;
};

#endif