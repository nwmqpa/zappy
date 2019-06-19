/*
** EPITECH PROJECT, 2019
** server_debug.c
** File description:
** debug file like server status printing.
*/

#include "server.h"
#include "logger.h"
#include "client.h"
#include "egg.h"

static const struct server_part_s SERVER_PARTS[] = {
    {"players", get_players_status},
    {"map", get_map_status},
    {"teams", get_teams_status},
    {NULL, NULL}
};

static debug_func get_func(char *part)
{
    for (int i = 0; SERVER_PARTS[i].name; ++i) {
        if (strcmp(part, SERVER_PARTS[i].name) == 0)
            return SERVER_PARTS[i].func;
    }
    return NULL;
}

char *server_status(server_t *server, const char *command)
{
    char *part = NULL;
    char *dupped = strdup(command);
    debug_func func;

    part = strtok(dupped, " \n");
    while (part != NULL) {
        func = get_func(part);
        if (func == NULL)
            errorl("Cannot find %s status.\n", part);
        else
            func(server);
        part = strtok(NULL, " \n");
    }
    free(dupped);
    return strdup("ok\n");
}
