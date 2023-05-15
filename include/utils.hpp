#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <unordered_map>
#include <filesystem>
#include <regex>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

enum class Face_direction
{
    North,
    South,
    East,
    West
};

const std::string Direction_string[4] =
    {
        "North", "South", "East", "West"};

namespace my_utils
{
    std::unordered_map<std::string, std::vector<std::string>> read_from_file(std::string name_of_the_file);
    std::string format_text(std::string text);
    std::queue<std::pair<std::string, std::string>> read_map(std::string name_of_the_file);
    std::string connect_strings_in_vector(std::vector<std::string> &vector_of_strings);
}

#endif