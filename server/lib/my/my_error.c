/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** my_error
*/

#include <stdio.h>
#include "lib.h"

/**
 * @brief Print an error message and exit the program
 * @details Print an error message and exit the program
 *
 * @param str the error message
*/
void my_error(const char *str)
{
    fprintf(stdout, "Error: %s\n", str);
    my_exit(84);
}
