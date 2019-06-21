/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** Utils functions.
*/

#include "utils.h"
#include "client.h"
#include "egg.h"

int join_str(char *insert, const char **to_join, char *join, size_t size)
{
    size_t y = 0;
    size_t i = 0;

    while (i < size) {
        if (to_join[y] != NULL) {
            sprintf(insert, "%s%s%s", insert, (y == 0) ? "" : join, to_join[y]);
            i++;
        }
        y++;
    }
    return 0;
}

void get_info_egg(void *data, const void *nothing)
{
    egg_t *egg = data;

    printf("Egg {\n"
            "   position: (x: %d, y: %d)\n"
            "   can_eclose: %s\n"
            "   time_left: %f\n"
            "}\n", egg->position.x, egg->position.y,
            egg->can_eclose ? "true" : "false", egg->time_left);
}

int client_cmp(const void *entry, const void *id)
{
    const ia_t *client = entry;
    int rhs = *((size_t *) id);

    return client->id == rhs;
}
