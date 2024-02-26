#include <player.hpp>

Player::Player(std::string name_, std::string species_, std::string fight_class_)
{
    name = name_;
    species = species_;
    fight_class = fight_class_;
    is_player = true;
}

std::unordered_map<std::string, std::string> Player::collect_player_info()
{
    std::unordered_map<std::string, std::string> to_return;
    to_return.insert({"name", name});
    to_return.insert({"species", species});
    to_return.insert({"fight_class", fight_class});
    return to_return;
}

void Player::leveling_up()
{
    stats.level++;
    stats.experience = 0;
}

void Player::add_experience(int additional_exp)
{
    stats.experience += additional_exp;
    if (stats.experience >= 100)
    {
        leveling_up();
    }
}

void Player::add_gold(int amount)
{
    stats.gold += amount;
}

void Player::add_item_ton_inv(std::unique_ptr<Item> some_item)
{
    inventory.push_back(std::move(some_item));
}

std::vector<std::string> Player::Item_info()
{
    std::vector<std::string> to_return;
    for (const auto &item : inventory)
    {
        to_return.push_back(item->get_name());
    }
    return to_return;
}

bool Player::put_item_as_armor(std::string item_name)
{
    if (!inventory.empty())
    {
        for (const auto &item : inventory)
        {
            if (item->get_name() == item_name)
            {
                if (item->check_type() == item_type::Armor)
                {
                    current_armor = item.get();
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

bool Player::put_item_as_weapon(std::string item_name)
{
    if (!inventory.empty())
    {
        for (const auto &item : inventory)
        {
            if (item->get_name() == item_name)
            {
                if (item->check_type() == item_type::Weapon)
                {
                    current_weapon = item.get();
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}