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

int main(int argc, char *argv[])
{
    options_t *options = create_opt(argc, argv);
    server_t *server = NULL;

    if (check_opt(options) == -1) {
        errorl("Error in argument parsing.\n");
        free(options);
        return 84;
    }
    server = create_server(options);
    print_opt(options);
    free(options);
    if (server) {
        return zappy_server(server);
    } else {
        return 84;
    }
}
