#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "console.hpp"
#include "utils.hpp"
#include "quest.hpp"

class Option;

class Node
{
protected:
    // Conteiners
    std::unordered_map<Face_direction, Node *> neighbors;
    std::vector<Option> options;
    std::vector<std::unique_ptr<Quest>> quests;
    std::vector<std::string> current_options;
    std::pair<unsigned int, unsigned int> position;

    // strings
    std::string name = "";
    std::string noteable_landmark;
    std::string Beginning_desription = "";

    // Status values
    bool action_done = false; // bolean value that informs if any action was done or if there was none possible here
    bool doing_quest = false;
    bool has_crossing = true;
    bool has_river = false;
    bool arrived = true;

public:
    // Constructors and destructors
    Node(){};
    Node(std::string descript, std::string landmark)
    {
        Beginning_desription = descript;
        noteable_landmark = landmark;
    };
    ~Node(){};

    void add_option(Option some_option);
    virtual bool exists_direction(Face_direction dir)
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
    virtual Node *get_neighbour(Face_direction dir) { return neighbors[dir]; };
    // Z tym mozna sprawdzac czy sa case sensitive itp
    bool check_availibility(std::string &some_text);
    virtual void add_neighbour(Node *neighb, Face_direction dir) { neighbors[dir] = neighb; };
    virtual std::string get_landmark() { return noteable_landmark; };
    virtual void assign_landmark(std::string landmark) { noteable_landmark = landmark; };
    virtual std::pair<unsigned int, unsigned int> get_coordinates() { return position; };
    virtual bool no_quests() { return quests.empty(); };
    virtual void add_quest(std::unique_ptr<Quest> some_quest) {quests.push_back(std::move(some_quest));};
    virtual void update(Console *console)
    {
        if (arrived)
        {
            console->add_new_text(Beginning_desription);
            arrived = false;
            if (no_quests())
            {
                console->add_new_text(display_options());
            }
            else
            {
                // Zacznij questa
            }
        }
        else if (doing_quest)
        {
        }
        else if (action_done)
        {
            console->add_new_text(display_options());
        }
    };
    // This function is going to return which node is next for picked option
    // Może da się to zrobić w check availibility funckcji by ustalic next noda i pozniej zwrocic
    Node *next_node(std::string text);
    std::string display_options();
};

#endif