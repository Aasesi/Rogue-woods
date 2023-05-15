#ifndef GAME_STATE_HPP_
#define GAME_STATE_HPP

#include "state.hpp"
#include "console.hpp"
#include "map.hpp"
#include <memory>
#include "player_input.hpp"

class Game_state : public State
{
private:

public:
    Game_state(const std::string path);
};

#endif