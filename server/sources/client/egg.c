/*
** EPITECH PROJECT, 2019
** egg.c
** File description:
** Egg source file.
*/

#include "egg.h"
#include "logger.h"

static const int ECLOSION_TIME = 600;

static int is_eclosable(const void *elem, const void *data)
{
    const egg_t *egg = elem;

    return egg->can_eclose;
}

int check_for_eggs(team_t *team, server_t *server)
{
    egg_t *egg = get_cmp_list(server->eggs, is_eclosable, NULL);

    if (egg == NULL) {
        infol("No egg able to eclose.\n");
        return -1;
    }
    for (int i = 0; team->clients[i]; ++i) {
        if (team->clients[i] == -2) {
            return i;
        }
    }
    infol("No slot available on team %s to connect.\n", team->name);
    return -1;
}

void eclosion_handler(void *elem, const void *data)
{
    time_server_t *params = (time_server_t *) data;
    egg_t *egg = (egg_t *) elem;

    if (egg->can_eclose)
        return;
    egg->time_left -= params->elapsed;
    if (egg->time_left <= 0)
        egg->can_eclose = 1;
}

egg_t *egg_create(int x, int y)
{
    egg_t *new = malloc(sizeof(egg_t));
    debugl("Creating a new egg on %d %d.\n", x, y);

    new->can_eclose = 0;
    new->time_left = ECLOSION_TIME;
    new->position.x = x;
    new->position.y = y;
    return new;
}

ia_t *egg_eclose(egg_t *egg, int fd)
{
    if (egg->can_eclose != 1) {
        errorl("Cannot eclose right now");
        return NULL;
    }
    ia_t *new = client_create(fd);
    new->position.x = egg->position.x;
    new->position.y = egg->position.y;
    return new;
}
