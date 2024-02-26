#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>
#include <unordered_map>

enum class item_type
{
    Armor,
    Weapon,
    Potion
};

class Item
{
private:
    std::string name;
    std::unordered_map<std::string, int> additional_statistics;
    item_type type_of_item;
public:
    Item();
    Item(std::string name_, std::unordered_map<std::string, int> add, item_type item);
    ~Item();
    std::string get_name(){return name;};
    item_type check_type(){return type_of_item;};
};

#endif