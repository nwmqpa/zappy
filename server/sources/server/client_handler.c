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

int handle_egg_client(client_t *client, server_t *server)
{
    team_t *team = get_client_team(client, server);
    int to_insert = 0;

    to_insert = check_for_eggs(team, server);
    if (to_insert != -1) {
        team->clients[to_insert] = client->id;
        return 1;
    }
    return 0;
}

void handle_protocol(client_t *client, server_t *server)
{
    char team_name[100] = {0};
    int free_space = -1;
    unsigned int x = rand() % (server->width - 1);
    unsigned int y = rand() % (server->height - 1);

    dprintf(client->id, "WELCOME\n");
    read(client->id, &team_name, 100);
    while ((free_space = add_client_to_team(server, client, team_name)) == -1) {
        dprintf(client->id, "ko\n");
        read(client->id, &team_name, 100);
    }
    if (free_space > 0 || handle_egg_client(client, server)) {
        add_player(get_tile_map(server->map, x, y), client->id);
        client->position.x = x;
        client->position.y = y;
    }
    dprintf(client->id, "%d\n%d %d\n", free_space - 1, server->width,
            server->height);
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
    team_t *team = NULL;

    debugl("Client delete handler.\n");
    client = pop_cmp_list( server->clients, client_cmp, (void *) &socket);
    if (!client) {
        errorl("Client %d not found.\n", socket);
        return 84;
    }
    infol("Deleting client %d.\n", client->id);
    team = get_client_team(client, server);
    remove_client_from_team(team, client, server);
    client_delete(client);
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
