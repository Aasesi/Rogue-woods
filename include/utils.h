#ifndef UTILS_H_
#define UTILS_H_

#include <unordered_map>
#include <filesystem>
#include <regex>
#include <string>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;


enum class Face_direction
{
    North,
    Northeast,
    Northwest,
    South,
    Southeast,
    Southwest,
    East,
    West
};

const std::string Direction_string[8] = 
{
	"North", "Northeast", "Northwest", "South", "Southeast", "Southwest", "East", "West"
};

namespace my_utils
{
    std::unordered_map<std::string, std::vector<std::string>> read_from_file(std::string name_of_the_file);
    std::string format_text(std::string text);
    
}


#endif