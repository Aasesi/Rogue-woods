#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#include "interface_element.hpp"
#include <vector>
#include <string>
#include "configs.hpp"

enum Direction
{
    Up,
    Down,
    None
};

class Console : public interface_element
{
private:
    Direction dir;
    std::vector<std::string> up_lines;
    std::vector<std::string> down_lines;
    std::string console_text;
    bool is_full = false;
    int curr_lines = 0;
    int const number_of_lines = 45;
    sf::Text _text;
    sf::Font _font;

public:
    Console(std::string path, sf::Vector2f position);
    void handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos) override;
    void update() override;
    void render(sf::RenderWindow &window) override;
    void add_new_text(std::string new_text);
    void get_focus();
    bool is_scrolled();
};

#endif