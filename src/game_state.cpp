#include "game_state.hpp"

Game_state::Game_state(const std::string path)
{
    this->background_texture.loadFromFile(path);
    this->background_sprite.setTexture(background_texture);
    this->background_sprite.setPosition(sf::Vector2f(0, 0));

    // Console
    std::unique_ptr<Console> con = std::make_unique<Console>(console_image, sf::Vector2f(442.f, 134.f));
    c = con.get();

    // Map
    std::unique_ptr<Map> mapa = std::make_unique<Map>(map_image, sf::Vector2f(1400.f, 132.f), 25);
    mapa_ = mapa.get();

    // Player input box
    std::unique_ptr<Player_input> p_i = std::make_unique<Player_input>(input_button_image, sf::Vector2f(442.f, 1064.f), con.get());
    pl_in = p_i.get();

    // Game information
    game_info = std::make_unique<basic_informations>();
    game_info->current_position = mapa->get_node(0, 0);
    game_info->player = std::make_unique<Player>("Your name", "Human", "Adventurer");

    // Niedokończone
    std::unique_ptr<Statistics_window> S_W = std::make_unique<Statistics_window>(stat_window_image, sf::Vector2f(17.f, 77.f),
                                                                                 game_info->player->collect_player_info(), game_info->player->get_stats());
    stats_window = S_W.get();

    // Map information window
    std::unique_ptr<Map_stats> m_s = std::make_unique<Map_stats>(mapstatswindow, sf::Vector2f(1416.f, 838.f), game_info->current_position->information_to_return());
    map_stats = m_s.get();

    game_sys = std::make_unique<Game_system>("Your name", "Human", "Adventurer", mapa_->get_node(0, 0), s_manager);

    // Adding interface elements
    add_interface_element(std::move(S_W));
    add_interface_element(std::move(mapa));
    add_interface_element(std::move(con));
    add_interface_element(std::move(p_i));
    add_interface_element(std::move(m_s));
}

void Game_state::update()
{
    for (auto &ptr : interface_elements)
    {
        ptr.get()->update();
    }
    if (pl_in->check_made_action())
    {
        switch (game_sys->get_status())
        {
        case Game_status::No_quests:
            // Execute strategy
            strategy = std::make_unique<Default_strategy>();
            // strategy->process_information(pl_in->retrive_picked_option(), game_info.get());
            strategy->process_information(game_sys.get(), pl_in->retrive_picked_option());
            break;
        case Game_status::Pop_up_quest:
            strategy = std::make_unique<Quest_strategy>();
            // strategy->process_information(pl_in->retrive_picked_option(), game_info.get());
            strategy->process_information(game_sys.get(), pl_in->retrive_picked_option());
            break;
        default:
            
            game_sys->get_text_to_display();
            break;
        }
       
        game_sys->add_text_to_console(c);
        game_sys->update_player_input_options(pl_in);
        game_sys->update_interface_elements(mapa_, map_stats, stats_window);
        if(game_sys->fight_start())
        {
            std::unique_ptr<Fight_state> fight = std::make_unique<Fight_state>(game_background, game_sys.get());
            fight->setManager(s_manager);
            s_manager->set_state_to_be_added(std::move(fight));
            s_manager->sygnalize_to_push();
        }
    }
}

void Game_state::interface_update()
{
    std::pair<unsigned int, unsigned int> coords = game_info->current_position->get_coordinates();
    mapa_->change_coordinates(coords.first, coords.second);
    map_stats->new_entire_info(game_info->current_position->information_to_return());
    stats_window->update_stats(game_info->player->get_stats());
}


void Game_state::start_function()
{
    game_info.get()->possible_options = game_info->current_position->see_options();
    pl_in->update_options(game_info->possible_options);
    std::string whole_string;
    for (const auto &opt : game_info->possible_options)
    {
        whole_string += "<" + opt + ">\n";
    }
    c->add_new_text(whole_string);
    game_info->status = Game_status::No_quests;
}