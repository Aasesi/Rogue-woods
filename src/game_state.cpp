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
    std::unique_ptr<Statistics_window> S_W = std::make_unique<Statistics_window>(stat_window_image, sf::Vector2f(17.f, 77.f), "Your name",
                                                                                 "Human", game_info->player->get_stats());
    stats_window = S_W.get();

    // Map information window
    std::unique_ptr<Map_stats> m_s = std::make_unique<Map_stats>(mapstatswindow, sf::Vector2f(1416.f, 838.f), game_info->current_position->information_to_return());
    map_stats = m_s.get();

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
        switch (game_info->status)
        {
        case Game_status::No_quests:
            // Execute strategy
            strategy = std::make_unique<Default_strategy>();
            strategy->process_information(pl_in->retrive_picked_option(), game_info.get());

            // Add text onto the screen
            c->add_new_text(game_info->text_to_display);

            // Update set of possible options for player input
            pl_in->update_options(game_info->possible_options);
            break;
        case Game_status::Pop_up_quest:
            strategy = std::make_unique<Quest_strategy>();
            strategy->process_information(pl_in->retrive_picked_option(), game_info.get());

            c->add_new_text(game_info->text_to_display);
            pl_in->update_options(game_info->possible_options);
            break;
        default:
            game_info.get()->possible_options = game_info->current_position->see_options();
            pl_in->update_options(game_info->possible_options);
            std::string whole_string;
            for (const auto &opt : game_info->possible_options)
            {
                whole_string += "<" + opt + ">\n";
            }
            c->add_new_text(whole_string);
            game_info->status = Game_status::No_quests;
            break;
        }
        // Map
        std::pair<unsigned int, unsigned int> coords = game_info->current_position->get_coordinates();
        mapa_->change_coordinates(coords.first, coords.second);
        map_stats->new_entire_info(game_info->current_position->information_to_return());
    }
}
