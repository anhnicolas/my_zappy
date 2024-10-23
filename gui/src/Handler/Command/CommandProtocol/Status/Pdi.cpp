/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pdi
*/

#include "Pdi.hpp"

void gui::Pdi::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pdi: can't be staged." << std::endl;
}

void gui::Pdi::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;

    iss >> token >> playerId;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");

    if (!gameData->playerExists(playerId))
        throw std::invalid_argument("Player does not exist");

    auto player = gameData->getPlayerById(playerId).value();
    player->kill(gameData);
}
