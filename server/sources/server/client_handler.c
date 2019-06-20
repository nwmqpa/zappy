/*
** EPITECH PROJECT, 2019
** client_handler.c
** File description:
** Client handler function callback.
*/

#include "map.h"
#include "logger.h"
#include "generic_list.h"
#include "client_commands.h"
#include "egg.h"
#include "events.h"

int handle_egg_client(client_t *client, server_t *server, const char *team_name)
{
    team_t *team = NULL;
    int to_insert = 0;

    for (int i = 0; server->teams[i]; i++) {
        if (strcmp(server->teams[i]->name, team_name) == 0) {
            team = server->teams[i];
            break;
        }
    }
    if (team == NULL)
        return 0;
    to_insert = check_for_eggs(team, server);
    if (to_insert != -1) {
        insert_head_list(team->clients, client);
        return 1;
    }
    return 0;
}

void handle_protocol(client_t *client, server_t *srv)
{
    char team_name[100] = {0};
    int slots = -1;

    dprintf(client->id, "WELCOME\n");
    read(client->id, &team_name, 100);
    while ((slots = add_client_to_team(srv, client, team_name)) == -1) {
        dprintf(client->id, "ko\n");
        read(client->id, &team_name, 100);
    }
    if (slots == 0) {
        dprintf(client->id, "ko\n");
        close(client->id);
    } else {
        add_player(get_tile_map(srv->map, client->position.x, client->position.y), client->id);
        dprintf(client->id, "%d\n%d %d\n", slots - 1, srv->width, srv->height);
    }
}

int on_connect_client(int socket, void *data)
{
    server_t *server = (server_t *) data;
    client_t *client = client_create(socket);

    debugl("Client connect handler.\n");
    client->id = socket;
    handle_protocol(client, server);
    insert_head_list(server->clients, (void *) client);
    return 0;
}

int on_delete_client(int socket, void *data)
{
    server_t *server = (server_t *) data;
    client_t *client = NULL;

    debugl("Client delete handler.\n");
    client = get_cmp_list( server->clients, client_cmp, (void *) &socket);
    if (!client) {
        errorl("Client %d not found.\n", socket);
        return 84;
    }
    infol("Deleting client %d.\n", client->id);
    kill_player(client, server);
    return 0;
}

int on_active_client(int socket, void *data)
{
    char buffer[1025] = {0};
    size_t bytes_read = read(socket, buffer, 1024);
    client_t *client = NULL;
    server_t *server = (server_t *) data;

    if (bytes_read == 0)
        return -1;
    client = get_cmp_list(server->clients, client_cmp, (void *) &socket);
    if (client == NULL) {
        errorl("Client with socket: %d not found.\n", socket);
        return -1;
    }
    add_command(client, strdup(buffer));
    debugl("Client active handler.\n");
    return 0;
}
