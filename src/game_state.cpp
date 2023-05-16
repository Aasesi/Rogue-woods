#include "game_state.hpp"

Game_state::Game_state(const std::string path)
{
    this->background_texture.loadFromFile(path);
    this->background_sprite.setTexture(background_texture);
    this->background_sprite.setPosition(sf::Vector2f(0, 0));
    // Tymczasowo mapa jest tak
    std::unique_ptr<Console> con = std::make_unique<Console>(console_image, sf::Vector2f(1300.f, 200.f));
    std::unique_ptr<Map> mapa = std::make_unique<Map>(console_image, sf::Vector2f(10.f, 10.f), 25, con.get());
    std::unique_ptr<Player_input> p_i = std::make_unique<Player_input>(input_button_image, sf::Vector2f(1320.f, 1150.f), con.get(), mapa.get());
    add_interface_element(std::move(mapa));
    add_interface_element(std::move(con));
    add_interface_element(std::move(p_i));
}