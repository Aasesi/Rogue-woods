#include "map.hpp"

Map::Map(std::string path, sf::Vector2f position, int size)
{
    this->interface_texture.loadFromFile(path);
    this->interface_sprite.setTexture(interface_texture);
    this->interface_sprite.setPosition(position);

    size_of_map = size;
    interface_texture2.loadFromFile(map_im);
    interface_sprite2.setTexture(interface_texture2);
    interface_sprite2.setPosition(position);
    interface_sprite2.setTextureRect(sf::IntRect(0, 0, 784, 636));

    point_texture.loadFromFile(point_on_map);
    point_sprite.setTexture(point_texture);
    point_sprite.setPosition(sf::Vector2f(position.x, position.y));
    
    coordinates = std::make_pair(position.x, position.y);

    make_map();
}

void Map::make_map()
{
    // Creating nodes
    make_nodes();
    // Making connections
    connect_in_grid();
    // Create basic options
    create_moving_options();
}

void Map::make_nodes()
{
    std::queue<std::pair<std::string, std::string>> node_info = my_utils::read_map("Map_nodes.txt");
    std::unordered_map<std::string, std::vector<std::string>> descript = my_utils::read_from_file("Locationdescription.txt");
    for (int i = 0; i < rows; i++)
    {
        std::vector<std::unique_ptr<Node>> new_nodes;
        for (int j = 0; j < columns; j++)
        {
            // Typ terenu
            std::string d = my_utils::connect_strings_in_vector(descript[node_info.front().second]);
            // To drugie z node_info to chyba nazwa miala być lecz moge się mylić
            new_nodes.emplace_back(std::make_unique<Node>(d, node_info.front().second, "Region not decided yet", "", i, j));
            node_info.pop();
        }
        nodes.push_back(std::move(new_nodes));
    }
}

void Map::connect_in_grid()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {

            if (j < columns - 1)
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
            if (i < rows - 1)
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

// Mozliwe ze mozna zamienic opcje na unique ptr moze idk zeby oszczedzic pamiec !!!
void Map::create_moving_options()
{
    std::unordered_map<std::string, std::vector<std::string>> keywords = my_utils::read_from_file("keywords.txt");
    for (auto &row : nodes)
    {
        for (auto &ptr : row)
        {
            // For every direction add option !! Can be done easier probably
            if (ptr.get()->exists_direction(Face_direction::North))
            {
                ptr.get()->add_option(make_option_for_ptr(ptr.get()->get_neighbour(Face_direction::North), keywords, Face_direction::North));
            }
            if (ptr.get()->exists_direction(Face_direction::South))
            {
                ptr.get()->add_option(make_option_for_ptr(ptr.get()->get_neighbour(Face_direction::South), keywords, Face_direction::South));
            }
            if (ptr.get()->exists_direction(Face_direction::East))
            {
                ptr.get()->add_option(make_option_for_ptr(ptr.get()->get_neighbour(Face_direction::East), keywords, Face_direction::East));
            }
            if (ptr.get()->exists_direction(Face_direction::West))
            {
                ptr.get()->add_option(make_option_for_ptr(ptr.get()->get_neighbour(Face_direction::West), keywords, Face_direction::West));
            }
        }
    }
}

Option Map::make_option_for_ptr(Node *text_for_ptr, std::unordered_map<std::string, std::vector<std::string>> keys, Face_direction dir)
{
    std::string option = "";
    std::string land = text_for_ptr->get_landmark();
    if (keys[land].size() <= 1)
    {
        option += "<" + Direction_string[static_cast<int>(dir)] + "> " + keys[land][0];
        Option some_option(option, Direction_string[static_cast<int>(dir)], "Move option", text_for_ptr);
        return some_option;
    }
    else
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, static_cast<unsigned int>(keys[land].size() - 1));
        option = "<" + Direction_string[static_cast<int>(dir)] + "> " + keys[land][dis(gen)];
        Option some_option(option, Direction_string[static_cast<int>(dir)], "Move option", text_for_ptr);
        return some_option;
    }
}

void Map::update()
{
}

void Map::handle_input(sf::Event &event, sf::RenderWindow &window, sf::Vector2f mousepos)
{
}

Node *Map::get_node(int row, int column)
{
    return nodes[row][column].get();
}

void Map::render(sf::RenderWindow &window)
{
    window.draw(this->interface_sprite);
    window.draw(this->interface_sprite2);
    window.draw(this->point_sprite);
}


void Map::change_coordinates(unsigned int x, unsigned int y)
{

    float a = 43.f * static_cast<float>(y);
    float b = 43.f * static_cast<float>(x);
    point_sprite.setPosition(sf::Vector2f(coordinates.first + a, coordinates.second + b));
}