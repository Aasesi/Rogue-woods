#ifndef PLAYER_INPUT_HPP_
#define PLAYER_INPUT_HPP_

#include "interface_element.hpp"
#include "console.hpp"
#include "configs.hpp"
#include <memory>

class Player_input : public interface_element
{
private:
    sf::Text _text;
    sf::Font _font;
    const std::string default_string = "WRITE YOUR MESSAGE HERE...";
    std::string input_text;
    bool clicked = false;
    bool sending_message = false;
    Console* console;

public:
    Player_input(std::string path, sf::Vector2f position, Console*console_ptr);
    void handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
};

#endif