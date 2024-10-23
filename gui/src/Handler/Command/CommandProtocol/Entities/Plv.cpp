/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Plv
*/

#include "Plv.hpp"

void gui::Plv::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    if (parameters.empty())
        throw std::invalid_argument("Invalid plv arguments");

    client->queueRequest("plv " + parameters);
}

void gui::Plv::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t level;

    iss >> token >> playerId >> level;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData->playerExists(playerId))
        throw std::invalid_argument("Player does not exist in the game data.");
    auto player = gameData->getPlayerById(playerId);
    if (player.has_value()) {
        if (player.value()->level() < level || level > 8)
            throw std::invalid_argument("Player level received does not match the player level in the game data.");
        player.value()->setLevel(level);
    }
}
