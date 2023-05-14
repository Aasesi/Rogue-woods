#ifndef MAP_HPP_
#define MAP_HHP_

#include "interface_element.hpp"
#include "node.hpp"
#include <memory>
#include "console.hpp"


class Map : public interface_element
{
public:
    Map(std::string path, sf::Vector2f position, int size, Console *console_ptr);
    void make_nodes();
    void connect_in_grid();
    void make_map();
    void make_connection(Node* first, Node* second, Face_direction dir);
private:
    std::vector<std::vector<std::unique_ptr<Node>>> nodes;
    Console *console;
    int size_of_map = 50;
};

#endif