/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** Utils functions.
*/

#include "utils.h"

// Put the to_join joinned by join to insert.
// Insert should be allocated.
int join_str(char *insert, const char **to_join, char join, size_t size)
{
    int offset = 0;
    int l_len = 0;
    size_t i = 0;
    int y = -1;

    for (i = 0; i < size; ++i) {
        if (to_join[++y] == NULL) {
            i--;
            continue;
        }
        l_len = strlen(to_join[y]);
        strncpy(insert + offset, to_join[y], l_len);
        offset += l_len + 1;
        if (i + 1 != size)
            insert[offset - 1] = join;
    }
    insert[offset] = 0;
    return 0;
}
