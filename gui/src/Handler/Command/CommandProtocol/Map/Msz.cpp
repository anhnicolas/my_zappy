/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Msz
*/

#include "Msz.hpp"

void gui::Msz::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    client->queueRequest("msz");
}

void gui::Msz::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;

    iss >> token >> x >> y;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    Vector2u size(x, y);

    if (gameData->map().size() != Vector2u(0, 0))
        throw std::invalid_argument("Map size already set.");
    gameData->map().initializeMap(size);
}
