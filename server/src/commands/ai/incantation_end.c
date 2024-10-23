/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** incantation
*/

#include "commands.h"
#include "packet.h"
#include "macros.h"
#include "clients.h"
#include "lib.h"
#include "zappy.h"
#include "time_utils.h"
#include <time.h>

/**
 * @brief 16-bit masks that determines the necessary
 * ressources for a incantation level.
 * @note They are stored in ascending order, first is the mask for leveling up
 * from level 1 to level 2, second is level 2 to 3, third for 3 to 4, etc...
 * @note Each value reprents the requirment to start or end an incantation
 * @note Every 2 bit starting from the end indicates an amount of rocks
 * @note The first bit is unused and the 3 bits after stands for player count
 */
static const uint16_t incantation_masks[7] = {
    0x1400, 0x2540, 0x2848, 0x4584, 0x4670, 0x66C4, 0x6AA9
};

/**
 * @brief Checks wethr a tile has necessary ressources for
 * a ritual at a given level
 *
 * @param level The ritual level
 * @param tile The tile the ritual is happening on
 * @return `true` if can start ritual, `false` otherwise.
 */
static bool check_tile_ressources(
    uint8_t level, player_list_t players, rocks_t rocks)
{
    uint16_t mask = 0;
    uint32_t count = get_list_size((node_t)players);

    if (level < 1 || level > 7)
        return false;
    mask = incantation_masks[level - 1];
    return (
        (mask >> 12 & 7) <= count &&
        (mask >> 10 & 3) <= rocks.linemate &&
        (mask >> 8 & 3) <= rocks.deraumere &&
        (mask >> 6 & 3) <= rocks.sibur &&
        (mask >> 4 & 3) <= rocks.mendiane &&
        (mask >> 2 & 3) <= rocks.phiras &&
        (mask >> 0 & 3) <= rocks.thystame
    );
}

/**
 * @brief Remove the rocks of a certain ritual level from the tile
 * @param level The ritual level
 * @param tile The tile
 */
static void consume_rocks(uint8_t level, tile_t tile)
{
    uint16_t mask = incantation_masks[level - 1];

    tile->rocks.linemate -= (mask >> 10 & 3);
    tile->rocks.deraumere -= (mask >> 8 & 3);
    tile->rocks.sibur -= (mask >> 6 & 3);
    tile->rocks.mendiane -= (mask >> 4 & 3);
    tile->rocks.phiras -= (mask >> 2 & 3);
    tile->rocks.thystame -= (mask >> 0 & 3);
}

/**
 * @brief Makes the player go up a level
 * @param player The player
 */
static void evolve(player_t player)
{
    char *msg = NULL;

    player->ritual = NULL;
    player->level++;
    msg = my_snprintf("Current level: %d", player->level);
    queue_packet_to_player(player, build_packet(msg));
    my_free(msg);
}

static void destroy_incantation(incantation_t ritual, server_info_t server)
{
    player_list_t next = NULL;

    remove_from_list((void *)ritual, (node_t *)&server->rituals);
    while (ritual->players) {
        next = ritual->players->next;
        my_free(ritual->players);
        ritual->players = next;
    }
    my_free(ritual);
}

/**
 * @brief Lets the player end an incantation ritual
 * @details starts an incantation.
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void end_incantation(
    UNUSED char **args,
    const client_t client,
    const server_info_t server_info)
{
    player_t player = client->player;
    incantation_t ritual = player->ritual;
    player_list_t players = player->ritual->players;
    tile_t tile = get_tile_at_position(player->position, server_info->map);
    uint8_t level = player->level;
    bool success = check_tile_ressources(level, players, tile->rocks);

    send_pie(player->ritual, success);
    for (; players; players = players->next) {
        if (success)
            evolve(players->player);
        else
            queue_packet_to_player(players->player, build_packet("ko"));
    }
    destroy_incantation(ritual, server_info);
    if (!success)
        return;
    consume_rocks(level, tile);
}
