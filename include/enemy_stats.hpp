#ifndef ENEMY_STATS_HPP_
#define ENEMY_STATS_HPP_

#include <interface_element.hpp>
#include <character.hpp>
#include <configs.hpp>
#include <unordered_map>

class Enemy_stats : public interface_element
{
public:
    Enemy_stats(){};
    Enemy_stats(std::string path, sf::Vector2f position, std::unordered_map<std::string, std::string> info_collection);
    ~Enemy_stats();
    void handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    void update_stats(std::unordered_map<std::string, std::string> info_collection);

private:
    std::unordered_map<std::string, std::string> text_to_display = {{"name", ""}, {"attack damage", ""}, {"defense", ""}, {"hp", ""}};
    std::string entire_string = "";
    sf::Text _text;
    sf::Font _font;
    bool got_new_information = true;
};

#endif