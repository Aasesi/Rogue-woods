#include "game_state.hpp"

Game_state::Game_state(const std::string path)
{
    this->background_texture.loadFromFile(path);
    this->background_sprite.setTexture(background_texture);
    this->background_sprite.setPosition(sf::Vector2f(0, 0));
    std::unique_ptr<Console> con = std::make_unique<Console>(console_image, sf::Vector2f(1300.f, 200.f));
    console = &con;
    add_interface_element(std::move(con));
}