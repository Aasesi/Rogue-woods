#ifndef MAPSTATS_HPP_
#define MAPSTATS_HPP_

#include <interface_element.hpp>
#include <configs.hpp>
#include <map>

class Map_stats : public interface_element
{
public:
    Map_stats(std::string path, sf::Vector2f position, std::map<std::string, std::string> some_info);
    void handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    void new_entire_info(std::map<std::string, std::string> info);

private:
    std::string entire_string = "";
    sf::Text _text;
    sf::Font _font;
    bool updated = true;
    std::map<std::string, std::string> info_to_show;
};

#endif