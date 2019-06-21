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
    for (size_t i = 0; i < size; ++i)
        sprintf(insert, "%s%s%s", insert, (i == 0) ? "" : join, to_join[i]);
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
