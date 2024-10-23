/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** linked_lists
*/

#pragma once

#include <stdint.h>

typedef struct node_s {
    struct node_s *next;
    struct node_s *prev;
    void *data;
} *node_t;

void add_to_list(void *new_data, node_t *list);
void remove_from_list(void *data, node_t *list);
node_t get_node_by_index(int index, node_t list);
int get_node_index(void *data, node_t list);
uint32_t get_list_size(node_t list);
