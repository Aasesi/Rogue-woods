#include <strategy_for_quest.hpp>

void Quest_strategy::process_information(std::string picked_option, basic_informations *informations)
{
    // Zmieniamy opcje
    informations->current_quest->next_option(picked_option);
    informations->text_to_display = informations->current_quest->get_description();
    // Sprawdzam czy jest konczaca opcja
    if (informations->current_quest->check_if_ends())
    {
        informations->status = Game_status::No_quests;
        informations->possible_options = informations->current_position->see_options();
        informations->text_to_display += "\n" + informations->current_position->Display_begin_description();
    }
    else
    {
        informations->possible_options = informations->current_quest->see_options();
    }
    // Dodaje do tekstu do wyswietlenia opcje
    informations->text_to_display += get_options(informations->possible_options);
}