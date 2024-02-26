#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_

#include <vector>
#include <stack>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "configs.hpp"

// I should change State so that it initializes with statemanager already and not with function that initializes it

class State;

enum class State_type
{
Fight_state,
Game_state
};


class State_manager
{
public:
    State_manager();
    void push(std::unique_ptr<State> state);
    void push_state_to_be_added();
    void pop();
    void handleinput(sf::Event& event, sf::RenderWindow& window, sf::Vector2f mousepos);
    void render(sf::RenderWindow& window);
    void update();
    void initialize();
    void sygnalize_to_pop(){pop_state = true;};
    void sygnalize_to_push(){push_state = true;};
    void set_state_to_be_added(std::unique_ptr<State> some_state);
    ~State_manager();
private:
    std::stack<std::unique_ptr<State>> states;
    std::unique_ptr<State> state_to_be_added;
    bool empty = true;
    bool push_state = false;
    bool pop_state = false;
};

#endif