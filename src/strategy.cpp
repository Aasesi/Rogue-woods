#include "strategy.hpp"

std::string Strategy::get_options(std::set<std::string> opts)
{
    std::string whole_string;
    for (const auto &opt : opts)
    {
        whole_string += "<" + opt + ">\n";
    }
    return whole_string;
}