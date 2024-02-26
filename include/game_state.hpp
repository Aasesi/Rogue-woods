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
#include <Statisticswindow.hpp>
#include <mapstats.hpp>
#include <game_system.hpp>
#include <Fight_state.hpp>

class Game_state : public State
{
private:
    std::unique_ptr<Strategy> strategy = nullptr;
    Player_input* pl_in;
    Console* c;
    Statistics_window* stats_window;
    Map_stats* map_stats;
    Map* mapa_;
    std::unique_ptr<basic_informations> game_info;
    std::unique_ptr<Quest_menu> quest_menu_;
    std::unique_ptr<Game_system> game_sys;
public:
    Game_state(const std::string path);
    void update() override;
    void interface_update();
    void start_function();
};

#endif