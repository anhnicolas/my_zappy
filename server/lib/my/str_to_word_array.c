/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** str_to_word_array
*/

#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "garbage_collector.h"

/**
 * @brief Count the number of words in a string
 * @details Count the number of words in a string using a delimiter
 *
 * @param str the string to count
 * @param delim the delimiters
 *
 * @return the number of words
*/
static size_t count_words(const char *str, const char *delim)
{
    size_t count = 0;
    char *start = my_strdup(str);
    char *keep = start;
    char *end;

    end = strpbrk(start, delim);
    while (end != NULL) {
        count++;
        start = end + 1;
        end = strpbrk(start, delim);
    }
    count++;
    my_free(keep);
    return count;
}

static char **transfer_to_array(const char *str, const char *delim)
{
    char **array = my_malloc(sizeof(char *) * (count_words(str, delim) + 1));
    int i = 0;
    char *start = my_strdup(str);
    char *end;
    char *keep = start;

    end = strpbrk(start, delim);
    while (end != NULL) {
        array[i] = my_strndup(start, end - start);
        i++;
        start = end + 1;
        end = strpbrk(start, delim);
    }
    array[i] = my_strdup(start);
    my_free(keep);
    i++;
    array[i] = NULL;
    return array;
}

/**
 * @brief Split a string into an array of words
 * @details Split a string into an array of words using a delimiter
 *
 * @param str the string to split
 * @param delim the delimiters
 *
 * @return the array of words
*/
char **str_to_word_array(const char *str, const char *delim)
{
    if (str == NULL || delim == NULL)
        return NULL;
    return transfer_to_array(str, delim);
}
