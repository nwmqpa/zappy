/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main file of the zappy server.
*/

#include "options.h"
#include "zappy.h"
#include "logger.h"
#include "server.h"

#ifndef TEST
int main(int argc, char *argv[])
{
    if (argc == 1) {
        dprintf(2, "zappy_server: Too few arguments.\n");
        return 84;
    }
    srandom(time(NULL));
    options_t *options = create_opt(argc, argv);
    server_t *server = NULL;

    if (check_opt(options) == -1) {
        free(options);
        return 84;
    }
    server = create_server(options);
    free(options);
    if (server)
        return zappy_server(server);
    else
        return 84;
}
#endif /* TEST */
