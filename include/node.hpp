#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <set>
#include "console.hpp"
#include "utils.hpp"
#include "quest.hpp"
#include "option.hpp"

class Node
{
protected:
    // Containers
    std::unordered_map<Face_direction, Node *> neighbors;
    std::vector<Option> basic_options;
    std::set<std::string> current_options;
    std::pair<unsigned int, unsigned int> position;

    // strings
    std::string name = "";
    std::string noteable_landmark;
    std::string Beginning_desription = "";
    std::string Region = "Not decided";

public:
    // Constructors and destructors
    Node(){};
    Node(std::string descript, std::string landmark)
    {
        Beginning_desription = descript;
        noteable_landmark = landmark;
    };
    Node(std::string descript, std::string landmark, std::string region, std::string name_, int x, int y);
    ~Node(){};

    void add_option(Option some_option);      
    bool exists_direction(Face_direction dir) 
    {
        if (neighbors.count(dir) != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    Node *get_neighbour(Face_direction dir) { return neighbors[dir]; };                
    bool check_availibility(std::string &some_text);                                  
    void add_neighbour(Node *neighb, Face_direction dir) { neighbors[dir] = neighb; }; 
    std::string get_landmark() { return noteable_landmark; };                          
    void assign_landmark(std::string landmark) { noteable_landmark = landmark; };      
    std::pair<unsigned int, unsigned int> get_coordinates() { return position; };      
    Node *next_node(std::string text);                                                 
    Option get_option(std::string text);                                               
    std::string Display_begin_description() { return Beginning_desription; };          
    std::set<std::string> see_options();                                               
    std::map<std::string, std::string> information_to_return();


    bool operator==(const Node &other);
};

#endif