/*
** EPITECH PROJECT, 2019
** look.c
** File description:
** Look around command file.
*/

#include "map.h"
#include "client_commands.h"

static char *get_view_level(int level, pos_t pos, map_t *map)
{
    int sub_level = level - 1;
    int begin = sub_level * -1;
    const char **stock = malloc(sizeof(char *) * sub_level);
    int total_len = 0;
    char *line;
    int idx = 0;
    char *ret;

    while (begin <= sub_level) {
        line = tile_to_string(get_tile_map(map, pos.x - begin, pos.y + level - 1));
        total_len += strlen(line) + 1;
        stock[idx++] = line;
        begin++;
    }
    if (level == 1)
        return line;
    ret = calloc(sizeof(char), total_len);
    join_str(ret, stock, ',', idx);
    return ret;
}

// Get vision use the player level, direction and position to give him what he
// can see on the tile in front of him.
// Example for north position and level 3:
//
//                   [...]
// [x - 1,y + 2][x + 0,y + 2][x + 1,y + 2]
//               [x + 0,y + 1]
//                    [P]
//
// where P is player.
// x is player x position.
// y is player y position.
// /!\ The world is spherical.
//
static char *get_vision_content(server_t *server, unsigned int level,
        unsigned int direction, pos_t position)
{
    char *buffer = NULL;
    char *tmp = NULL;
    char *new = NULL;

    for (unsigned int i = 1; i <= level; ++i) {
        new = get_view_level(i, position, server->map);
        if (tmp != NULL)
            asprintf(&buffer, "%s,%s", tmp, new);
        else
            buffer = new;
        tmp = buffer;
    }
    asprintf(&buffer, "[%s]", tmp);
    return buffer;
}

char *look(client_t *client, server_t *server)
{
    client->cooldown = 7;
    return get_vision_content(server, client->level, client->direction,
            client->position);
}
