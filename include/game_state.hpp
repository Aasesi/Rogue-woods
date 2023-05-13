#ifndef GAME_STATE_HPP_
#define GAME_STATE_HPP

#include "state.hpp"
#include "console.hpp"
#include <memory>

class Game_state : public State
{
private:
    std::unique_ptr<Console>* console;

public:
    Game_state(const std::string path);
};

#endif