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


class State_manager
{
public:
    State_manager();
    void push(std::unique_ptr<State> state);
    void pop();
    void handleinput(sf::Event& event, sf::RenderWindow& window, sf::Vector2f mousepos);
    void render(sf::RenderWindow& window);
    void update();
    void initialize();
    ~State_manager();
private:
    std::stack<std::unique_ptr<State>> states;
    bool empty = true;
};

#endif