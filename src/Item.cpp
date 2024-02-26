#include <Item.hpp>

Item::Item()
{

}

Item::Item(std::string name_, std::unordered_map<std::string, int> stats, item_type item)
{
    name=name_;
    additional_statistics = stats;
    type_of_item = item;   
}

Item::~Item()
{
    
}