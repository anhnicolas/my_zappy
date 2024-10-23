/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** global_packet_send
*/

#include "packet.h"
#include "clients.h"
#include "garbage_collector.h"
#include <string.h>

/**
 * @brief Queue a packet to all clients of a specific type
 * @details Queue a packet to all clients of a specific type
 *
 * @param type the type of the client
 * @param packet the packet to send
 */
void queue_packet_to_client_type(const enum CLIENT_TYPE type,
    packet_t *packet)
{
    client_list_t clients = get_clients_by_type(type);
    client_list_t tmp = clients;
    packet_t *packet_copy;

    while (tmp) {
        packet_copy = my_malloc(sizeof(packet_t));
        memcpy(packet_copy, packet, sizeof(packet_t));
        add_packet_to_queue(&tmp->client->packet_queue, packet_copy);
        tmp = tmp->next;
    }
}

/**
 * @brief Queue a packet to a client by using its refered player.
 * @details It actually compares player ids
 *
 * @param player The player's client to send to
 * @param packet The packet to send
 */
void queue_packet_to_player(player_t player, packet_t *packet)
{
    client_list_t *clients = get_clients();
    client_list_t node = *clients;
    player_t other = NULL;

    while (node) {
        other = node->client->player;
        if (other && player->player_number == other->player_number)
            add_packet_to_queue(&node->client->packet_queue, packet);
        node = node->next;
    }
}
