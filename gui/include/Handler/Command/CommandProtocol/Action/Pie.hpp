/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pie
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Pie : public ICommand {
        public:
            /**
             * @brief The command Pie sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command gets result when an incantation is done
             * @note Receives the command: pie X Y R
             * @note X Y -> x and y position
             * @note R -> result of the incantation
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
