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
    // Text 
    sf::Text _text;
    sf::Font _font;
    const std::string default_string = "Write your message here...";
    std::string input_text;

    // Option strings and connected functionalities
    int size_of_basic_options = 1;
    std::set<std::string> options;
    std::string picked_option;
    
    // Boolean values
    bool clicked = false;
    bool sending_message = false;
    bool made_action = true;
    
    // Required objects
    Console* console;

public:
    Player_input(std::string path, sf::Vector2f position, Console*console_ptr);
    void handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    bool check_option_availibility(std::string& text);
    std::string retrive_picked_option();
    bool check_made_action();
    void update_options(std::set<std::string> opt){options = opt;};
};

#endif