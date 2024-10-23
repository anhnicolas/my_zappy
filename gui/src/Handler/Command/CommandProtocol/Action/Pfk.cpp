/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pfk
*/

#include "Pfk.hpp"

void gui::Pfk::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pfk: can't be staged." << std::endl;
}

void gui::Pfk::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;

    iss >> token >> playerId;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData->playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    auto player = gameData->getPlayerById(playerId);
    if (player.has_value())
        player.value()->layEgg(true);
}
