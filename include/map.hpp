#ifndef MAP_HPP_
#define MAP_HPP_

#include <interface_element.hpp>
#include "node.hpp"
#include <memory>
#include "console.hpp"
#include "option.hpp"
#include <random>
#include "quest.hpp"


class Map: public interface_element
{
public:
    Map(std::string path, sf::Vector2f position, int size); //
    void make_nodes(); //
    void connect_in_grid(); //
    void make_map(); //
    void make_connection(Node* first, Node* second, Face_direction dir); //
    void create_moving_options(); //
    Option make_option_for_ptr(Node* text_for_ptr, std::unordered_map<std::string, std::vector<std::string>> keys, Face_direction dir); //
    void handle_input(sf::Event& event, sf::RenderWindow& window, sf::Vector2f mousepos) override; //
    void update() override; //
    Node* get_node(int row, int column); //
    void render(sf::RenderWindow& window) override;
    void change_coordinates(unsigned int x, unsigned int y);
    
private:
    // Nodes
    std::vector<std::vector<std::unique_ptr<Node>>> nodes;

    sf::Texture interface_texture2;
    sf::Sprite interface_sprite2;

    // Map configuration
    int size_of_map = 630; // 35x8 tyle ma być, ale zaczne od 10 x 10
    int rows = 6;
    int columns = 17;

    // Location on map
    sf::Texture point_texture;
    sf::Sprite point_sprite;
    std::pair<float, float> coordinates;
};

#endif