#ifndef PLAYER_INPUT_HPP_
#define PLAYER_INPUT_HPP_

#include "interface_element.hpp"
#include "console.hpp"
#include "map.hpp"
#include "configs.hpp"
#include <memory>

class Player_input : public interface_element
{
private:
    sf::Text _text;
    sf::Font _font;
    const std::string default_string = "Write your message here...";
    std::string input_text;
    // Boolean values
    bool clicked = false;
    bool sending_message = false;
    // Required objects
    Console* console;
    Map* map;

public:
    Player_input(std::string path, sf::Vector2f position, Console*console_ptr, Map* map_ptr);
    void handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    bool check_option_availibility(std::string& text);
};

#endif