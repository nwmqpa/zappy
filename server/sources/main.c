/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main file of the zappy server.
*/

#include "options.h"
#include "zappy.h"

int main(int argc, char *argv[])
{
    options_t *options = create_opt(argc, argv);
    print_opt(options);
    zappy_server(options);
    return 0;
}
