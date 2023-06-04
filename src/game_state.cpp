#include "game_state.hpp"

Game_state::Game_state(const std::string path)
{
    this->background_texture.loadFromFile(path);
    this->background_sprite.setTexture(background_texture);
    this->background_sprite.setPosition(sf::Vector2f(0, 0));
    // Tymczasowo mapa jest tak
    std::unique_ptr<Console> con = std::make_unique<Console>(console_image, sf::Vector2f(1300.f, 200.f));
    c = con.get();
    std::unique_ptr<Map> mapa = std::make_unique<Map>(console_image, sf::Vector2f(10.f, 10.f), 25);
    std::unique_ptr<Player_input> p_i = std::make_unique<Player_input>(input_button_image, sf::Vector2f(1320.f, 1150.f), con.get());
    game_info = std::make_unique<basic_informations>();
    game_info->current_position = mapa->get_node(1, 1);
    pl_in = p_i.get();
    add_interface_element(std::move(mapa));
    add_interface_element(std::move(con));
    add_interface_element(std::move(p_i));
    quest_menu_ = std::make_unique<Quest_menu>();
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
            c->add_new_text( whole_string);
            game_info->status = Game_status::No_quests;
            break;
        }
    }
}
