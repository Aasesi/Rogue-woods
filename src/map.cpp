#include "map.hpp"

Map::Map(std::string path, sf::Vector2f position, int size, Console *console_ptr)
{
    this->interface_texture.loadFromFile(path);
    this->interface_sprite.setTexture(interface_texture);
    this->interface_sprite.setPosition(position);
    console = console_ptr;
    nodes.reserve(size);
    make_map();
}

void Map::make_map()
{
    make_nodes();
    connect_in_grid();
}

void Map::make_nodes()
{
    std::queue<std::pair<std::string, std::string>> node_info = my_utils::read_map("Map_nodes.txt");
    for (int i = 0; i < size_of_map; i++)
    {
        for (int j = 0; j < size_of_map; j++)
        {
            nodes[i].emplace_back(std::make_unique<Node>());
        }
    }
}

void Map::connect_in_grid()
{
    for (int i = 0; i < size_of_map; ++i)
    {
        for (int j = 0; j < size_of_map; ++j)
        {

            if (j < size_of_map - 1)
            {
                make_connection(nodes[i][j].get(), nodes[i][j + 1].get(), Face_direction::East);
            }

            // Connect west node
            if (j > 0)
            {
                make_connection(nodes[i][j].get(), nodes[i][j - 1].get(), Face_direction::West);
            }

            // Connect north node
            if (i > 0)
            {
                make_connection(nodes[i][j].get(), nodes[i - 1][j].get(), Face_direction::North);
            }

            // Connect south node
            if (i < size_of_map - 1)
            {
                make_connection(nodes[i][j].get(), nodes[i + 1][j].get(), Face_direction::South);
            }
        }
    }
}

void Map::make_connection(Node *first, Node *second, Face_direction dir)
{
    first->add_neighbour(second, dir);
}