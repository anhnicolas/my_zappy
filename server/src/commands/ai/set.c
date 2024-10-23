/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** set
*/

#include "commands.h"
#include "commands_utils.h"
#include "packet.h"
#include "clients.h"
#include "zappy.h"

/**
 * @brief Gets the first argument if there is one
 * @param args the argument list
 * @return NULL if it failed, the first arg if there is one.
 */
static const char *get_content_arg(char **args)
{
    uint32_t count = tablen((const void **)args);

    if (count != 2)
        return NULL;
    return args[1];
}

/**
 * @brief Sends pdr #n i to the graphical client
 * @param player_number The player that dropped something
 * @param ressource The name of the ressource
 */
static void send_pdr(uint32_t player_number, const char *ressource)
{
    int8_t id = get_ressource_id(ressource);

    if (id < 0)
        return;
    queue_to_graphical(my_snprintf("pdr %d %d", player_number, id));
}

/**
 * @brief Set command
 * @details Sets down an item from a player's inventory
 *
 * @param args the arguments of the command
 * @param client the client that executed the command
 * @param server_info the server info
 */
void set(
    char **args,
    const client_t client,
    UNUSED const server_info_t server_info)
{
    player_t player = client->player;
    tile_t tile = NULL;
    const char *arg = get_content_arg(args);

    if (arg == NULL) {
        throw_ko(client);
        return;
    }
    tile = get_tile_at_position(player->position, server_info->map);
    if (!player_pick_up(arg, player, tile, -1)) {
        throw_ko(client);
        return;
    }
    add_packet_to_queue(&client->packet_queue, build_packet("ok"));
    change_map_ressource(arg, server_info, 1);
    send_pdr(player->player_number, arg);
}
