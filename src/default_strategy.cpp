#include "default_strategy.hpp"

void Default_strategy::process_information(std::string picked_option, basic_informations *informations)
{
    informations->current_position = informations->current_position->next_node(picked_option);
    informations->possible_options = informations->current_position->see_options();
    std::string whole_string;
    for(const auto& opt: informations->possible_options)
    {
        whole_string += "<" + opt + ">\n";
    }
    informations->text_to_display = informations->current_position->Display_begin_description() + whole_string;
}
