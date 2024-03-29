#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include <unordered_map>
#include <filesystem>
#include <regex>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "quest_option.hpp"

namespace fs = std::filesystem;

enum class Face_direction
{
    North,
    South,
    East,
    West
};

struct statistics
{
    int hp = 100;
    int mana = 100;
    int level = 1;
    int experience = 0;

    int inteligence = 10;
    int strength = 10;
    int dexterity = 10;
    int vitality = 10;
    int charisma = 10;

    int gold = 0;
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
    std::vector<std::unique_ptr<Quest_option>> extract_text_for_quest(std::string name_of_the_file);
}

#endif