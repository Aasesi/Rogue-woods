#include "default_strategy.hpp"

void Default_strategy::process_information(std::string picked_option, basic_informations *informations)
{
    informations->current_position = informations->current_position->next_node(picked_option);
    // Generate quest
    if (check_chance(informations->chance_of_spawning_quest))
    {
        std::string name = "The_lost_ring_quest.txt";
        informations->current_quest = std::make_unique<Fast_quest>(name);
        informations->status = Game_status::Pop_up_quest;
        informations->possible_options = informations->current_quest->see_options();
        informations->text_to_display = informations->current_quest->get_description();
    }
    else
    {
        informations->possible_options = informations->current_position->see_options();
        informations->text_to_display = informations->current_position->Display_begin_description();
    }
    informations->text_to_display += get_options(informations->possible_options);
}

void Default_strategy::process_information(Game_system *game_system, std::string picked_option)
{
    game_system->go_to_next_node(picked_option);
    if (check_chance(0.8))
    {
        game_system->generate_fast_quest();
        game_system->change_game_status(Game_status::Pop_up_quest);
    }
    game_system->get_text_to_display();
}

bool Default_strategy::check_chance(double chance)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double randomValue = distribution(generator);
    if (randomValue < chance)
    {
        return true;
    }
    return false;
}