/*
** EPITECH PROJECT, 2019
** special_function.c
** File description:
** Special functions
*/

#include "incante.h"

int prepare_special_command(ia_t *client, server_t *server)
{
    if (strncmp(client->to_exec, "Incante", 7) == 0) {
        prepare_incante(client, server);
        return 1;
    }
    return 0;
}
