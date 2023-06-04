#ifndef GAME_STATE_HPP_
#define GAME_STATE_HPP

#include "state.hpp"
#include "console.hpp"
#include "map.hpp"
#include <memory>
#include "player_input.hpp"
#include "strategy.hpp"
#include "default_strategy.hpp"
#include "quest_menu.hpp"
#include <strategy_for_quest.hpp>



class Game_state : public State
{
private:
    std::unique_ptr<Strategy> strategy = nullptr;
    Player_input* pl_in;
    Console* c;
    std::unique_ptr<basic_informations> game_info;
    std::unique_ptr<Quest_menu> quest_menu_;
public:
    Game_state(const std::string path);
    void update() override;
};

#endif