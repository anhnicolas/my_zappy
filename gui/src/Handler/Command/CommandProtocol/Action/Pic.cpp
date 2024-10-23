/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pic
*/

#include "Pic.hpp"

void gui::Pic::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pic: can't be staged." << std::endl;
}

void gui::Pic::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;
    std::uint32_t level;
    std::uint32_t playerId;

    iss >> token >> x >> y >> level;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (x >= gameData->map().size().x() || y >= gameData->map().size().y())
        throw std::invalid_argument("Invalid tile coordinates, out of map bounds.");
    while (iss >> playerId) {
        auto players = gameData->getPlayerById(playerId);
        if (players.has_value()) {
            if (!gameData->playerExists(playerId))
                throw std::invalid_argument("Player does not exist");
            if (players.value()->position().x() != x || players.value()->position().y() != y)
                throw std::invalid_argument("Player position does not match the position in the game data.");
            if (players.value()->level() != level)
                throw std::invalid_argument("Player level does not match the level in the game data.");
            players.value()->incantate();
        }
    }
}
