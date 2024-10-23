/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Edi
*/

#include "Edi.hpp"

void gui::Edi::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command edi: can't be staged." << std::endl;
}

void gui::Edi::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t eggId;

    iss >> token >> eggId;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData->eggExists(eggId))
        throw std::invalid_argument("Egg does not exist");
    auto egg = gameData->getEggById(eggId);
    if (egg.has_value())
        egg.value()->kill();
}
