#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "console.hpp"
#include "utils.hpp"

class Node;
struct Option
{
    std::string description;
    Node *nextnode;
};

class Node
{
protected:
    std::unordered_map<Face_direction, Node *> neighbors;
    bool land_locked = false;
    std::vector<Option> options;
    std::string name = "";
    std::pair<unsigned int, unsigned int> position;
    std::string noteable_landmark;
    std::string Beginning_desription = "";
    bool quest_was_done = false;

public:
    Node(){};
    ~Node(){};
    virtual void add_option(Option some_option) { options.push_back(some_option); };
    virtual std::string merge_all_options()
    {
        std::string result;
        std::for_each(options.begin(), options.end(), [&](const Option &option)
                      { result += option.description; });
        return result;
    };
    virtual Node *get_neighbour(Face_direction dir) { return neighbors[dir]; };
    virtual void add_neighbour(Node *neighb, Face_direction dir) { neighbors[dir] = neighb; };
    virtual std::string get_landmark() { return noteable_landmark; };
    virtual void assign_landmark(std::string landmark) { noteable_landmark = landmark; };
    // Zrób tu 0 pożniej jak zrobisz dziedziczenie
    virtual void update() {};
    virtual std::pair<unsigned int, unsigned int> get_coordinates() { return position; };
};

#endif