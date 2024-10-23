/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pdr
*/

#include "Pdr.hpp"

void gui::Pdr::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pdr: can't be staged." << std::endl;
}

void gui::Pdr::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t ressourceId;

    iss >> token >> playerId >> ressourceId;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData->playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    auto player = gameData->getPlayerById(playerId);
    player.value()->dropRessource();
}
