/*
** EPITECH PROJECT, 2019
** debug.c
** File description:
** Debug functions.
*/

#include "server.h"
#include "egg.h"

void get_info_eggs(void *entry, const void *nothing)
{
    printf("Eclose in: %f\n", ((egg_t *) entry)->time_left);
    printf("Can eclose: %d\n", ((egg_t *) entry)->can_eclose);
}


void get_info_player(void *player, const void *nothing)
{
    ia_t *client = player;

    print_client(client);
}

void get_players_status(server_t *server)
{
    map(server->clients, get_info_player, NULL);
    for (int i = 0; server->teams[i]; i++) {
        map(server->teams[i]->eggs, get_info_eggs, NULL);
    }
}

void get_map_status(server_t *server)
{
    tile_t *tile = NULL;

    for (int y = server->height - 1; y >= 0; --y) {
        printf("%2d | ", y);
        for (unsigned int x = 0; x < server->width; ++x) {
            tile = get_tile_map(server->map, x, y);
            printf("[%d]", tile->nb_player);
        }
        putchar('\n');
    }
    putchar('\n');
}

void get_teams_status(server_t *server)
{
    ia_t *client = 0x0;
    int nb_client = 0;
    int value_c = 0;

    for (int i = 0; server->teams[i]; ++i) {
        for (int y = 0; y < server->client_per_team; ++y) {
            client = get_cmp_list(server->teams[i]->clients, client_cmp, &y);
            value_c = client->id;
            nb_client = (value_c != 0 && value_c != -1)
                ? nb_client + 1 : nb_client;
        }
        printf("There is %d clients in team: %s.\n", nb_client,
                server->teams[i]->name);
        nb_client = 0;
    }
}
