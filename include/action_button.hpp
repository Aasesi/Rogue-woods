#ifndef ACTION_BUTTON_HPP_
#define ACTION_BUTTON_HPP_

#include "interface_element.hpp"
#include <iostream>

enum class action_type
{
    Attack,
    Defend,
    Spell,
    None
};

class action_button : public interface_element
{
public:
    action_button();
    action_button(std::string path, sf::Vector2f position, action_type type_of_button);
    ~action_button();
    void handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos) override;
    void update() override;
    bool is_pressed(){return pressed;};
    action_type get_action_type(){return action_performed;};
    void change_pressed(){pressed= false;};

private:
    bool pressed = false;
    bool action_done = false;
    action_type action_performed;
};

#endif