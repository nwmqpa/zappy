/*
** EPITECH PROJECT, 2019
** zappy.c
** File description:
** zappy source file main loop.
*/

#include <time.h>
#include "zappy.h"
#include "logger.h"
#include "dispatcher.h"
#include "handlers.h"
#include "client_commands.h"
#include "egg.h"
#include "events.h"
#include "server.h"

static void handle_cooldown(ia_t *client, server_t *server, int elapsed)
{
    char *to_send = NULL;

    client->cooldown = 0;
    if (client->to_exec) {
        to_send = process_command(client, server);
        dprintf(client->id, "%s\n", to_send);
        free(to_send);
        free(client->to_exec);
        client->to_exec = NULL;
    }
    prepare_command(client, server);
}

static void handle_team_tick(void *data, const void *params)
{
    team_t *team = data;
    map(team->eggs, eclosion_handler, (void *) params);
}

static void handle_player_tick(void *data, const void *params)
{
    const time_server_t *parameters = (time_server_t *) params;
    ia_t *client = data;
    double elapsed_time = parameters->elapsed;

    client->cooldown -= elapsed_time;
    client->need_to_eat -= elapsed_time;
    if (client->need_to_eat <= 0 && client->inventory.inv.food == 0) {
        kill_player(client, parameters->server);
    } else if (client->need_to_eat <= 0) {
        client->inventory.inv.food -= 1;
        client->need_to_eat = 126;
    }
    if (client->cooldown <= 0)
        handle_cooldown(client, parameters->server, elapsed_time);
}

void tick_system(server_t *server)
{
    static struct timespec old = {0};
    struct timespec new = {0};
    time_server_t name = (time_server_t) { 0, server };

    if (memcmp(&old, &new, sizeof(old)) == 0)
        clock_gettime(CLOCK_MONOTONIC, &old);
    clock_gettime(CLOCK_MONOTONIC, &new);
    name.elapsed = (new.tv_sec - old.tv_sec) * 1e9;
    name.elapsed = (name.elapsed + (new.tv_nsec - old.tv_nsec)) * 1e-9;
    name.elapsed *= server->freq;
    clock_gettime(CLOCK_MONOTONIC, &old);
    map(server->clients, handle_player_tick, &name);
    for (int i = 0; server->teams[i]; i++)
        handle_team_tick(server->teams[i], &name);
    server->map->time_respawn -= name.elapsed;
    if (server->map->time_respawn <= 0) {
        infol("Respwaning ressources.\n");
        server->map->time_respawn = TIME_RESPAWN;
        respawn_ressources(server->map, server);
    }
}

int run_dispatch(dispatcher_t *g, dispatcher_t *c, server_t *s)
{
    while (42) {
        if (dispatch(g, s) == -1 || dispatch(c, s) == -1) {
            infol("Closing server after an error.\n");
            return -1;
        }
        tick_system(s);
        handle_events(s);
    }
    return 0;
}
