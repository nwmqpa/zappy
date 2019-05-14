/*
** EPITECH PROJECT, 2018
** zappy_ai
** File description:
** get arguments with get_opt_long
*/

#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "my_ai.h"

int verif_port(char *str)
{
    int port = 0;

    for (int i = 0; str[i] != 0; i++)
        if (str[i] < '0' || str[i] > '9')
            return (-1);
    port = atoi(str);
    if (port <= 0 || port > 65535)
        return (-1);
    return (0);
}

int switch_norm_2(int c, arguments_t *args_t)
{
    switch (c) {
    case 'p':
        if (verif_port(optarg) == -1)
            print_help(84);
        args_t->port = atoi(optarg);
        break;
    case 'h':
        args_t->machine = strdup(optarg);
        break;
    case '?':
        return (84);
    case ':':
        return (84);
    default:
        break;
    }
    return (0);
}

int switch_norm_1(int c, arguments_t *args_t)
{
    switch (c) {
    case 0:
        args_t->port = 0;
        break;
    case 'n':
        args_t->name = strdup(optarg);
        break;
    default:
        if (switch_norm_2(c, args_t) == 84)
            return (84);
    }
    return (0);
}

int get_opt(int argc, char **argv, arguments_t *args_t)
{
    struct option long_options[] = {
        {"port", 1, 0, 'p'},
        {"name", 1, 0, 'n'},
        {"machine", 1, 0, 'h'},
        {0, 0, 0, 0}
    };

    for (int c; 1;) {
        c = getopt_long(argc, argv, "p:n:h:", long_options, NULL);
        if (c == -1)
            break;
        if (switch_norm_1(c, args_t) == 84)
            return (84);
    }
    return (optind < argc ? 84 : 0);
}