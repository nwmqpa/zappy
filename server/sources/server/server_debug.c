/*
** EPITECH PROJECT, 2019
** server_debug.c
** File description:
** debug file like server status printing.
*/

#include "server.h"
#include "logger.h"
#include "client.h"

void get_info_player(void *player, const void *nothing) {
    client_t *client = player;

    print_client(client);
}

void get_players_status(server_t *server) {
    map(server->clients, get_info_player, NULL);
}

void get_map_status(server_t *server) {
    tile_t *tile = NULL;

    for (int y = server->height; y >= 0; --y) {
        printf("%2d | ", y);
        for (unsigned int x = 0; x < server->width; ++x) {
            tile = get_tile_map(server->map, x, y);
            printf("[%d]", tile->nb_player);
        }
        putchar('\n');
    }
    putchar('\n');
}

void get_teams_status(server_t *server) {
    int nb_client = 0;
    int value_c = 0;

    for (int i = 0; server->teams[i]; ++i) {
        for (int y = 0; y < server->client_per_team; ++y) {
            value_c = server->teams[i]->clients[y];
            nb_client = (value_c != 0 && value_c != -2 && value_c != -1)
                ? nb_client + 1 : nb_client;
        }
        printf("There is %d clients in team: %s.\n", nb_client,
                server->teams[i]->name);
        nb_client = 0;
    }
}

static const struct server_part_s SERVER_PARTS[] = {
    {"players", get_players_status},
    {"map", get_map_status},
    {"teams", get_teams_status},
    {NULL, NULL}
};

static debug_func get_func(char *part) {
    for (int i = 0; SERVER_PARTS[i].name; ++i) {
        if (strcmp(part, SERVER_PARTS[i].name) == 0)
            return SERVER_PARTS[i].func;
    }
    return NULL;
}

char *server_status(server_t *server, const char *command) {
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
