#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "interface_element.hpp"
#include "state.hpp"
#include "game_state.hpp"

enum class type_of_button
{
    Play_button,
    Exit_button
};

class Button : public interface_element
{
public:
    Button(const std::string path, sf::Vector2f position, type_of_button b, std::shared_ptr<State_manager> s_m);
    void handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos) override;
    void update() override;
private:
    type_of_button button_type;
    std::shared_ptr<State_manager> state_m = nullptr;
};

#endif