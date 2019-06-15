/*
** EPITECH PROJECT, 2019
** client.c
** File description:
** main client file.
*/

#include "logger.h"
#include "client_commands.h"

void move_client(client_t *client, server_t *server, pos_t new, pos_t size)
{
    tile_t *new_tile = NULL;
    tile_t *old_tile = get_tile_map(server->map, client->position.x,
            client->position.y);

    remove_player(old_tile, client->id);
    client->position.x += new.x;
    client->position.y += new.y;
    client->position.x %= size.x;
    client->position.y %= size.y;
    if (client->position.x < 0)
        client->position.x = size.x + new.x;
    if (client->position.y < 0)
        client->position.y = size.y + new.y;
    new_tile = get_tile_map(server->map, client->position.x,
            client->position.y);
    add_player(new_tile, client->id);
}

client_t *client_create(int id)
{
    client_t *new = calloc(sizeof(client_t), 1);

    new->commands = create_list();
    new->id = id;
    new->inventory.inv.food = 10;
    new->level = 1;
    return new;
}

// TODO: Remove player from team.
void client_delete(client_t *client)
{
    if (client->to_send != NULL)
        free(client->to_send);
    empty_list(client->commands, free);
    dprintf(client->id, "dead\n");
}

void print_client(client_t *client)
{
    char *inv = inventory(client, NULL);
    const char *direction = NULL;

    if (client->direction == 0)
        direction = "LEFT";
    else if (client->direction == 1)
        direction = "RIGHT";
    else if (client->direction == 2)
        direction = "UP";
    else
        direction = "DOWN";

    printf("Client {\n"
            "   id: %d\n"
            "   inventory: %s\n"
            "   position: (x: %d, y: %d)\n"
            "   level: %d\n"
            "   cooldown: %d\n"
            "   to_send: %s\n"
            "   direction: %s\n"
            "}\n"
            , client->id, inv, client->position.x,
            client->position.y, client->level, client->cooldown,
            client->to_send, direction);
    free(inv);
}

void print_client_list(const void *data)
{
    print_client((client_t *) data);
}
