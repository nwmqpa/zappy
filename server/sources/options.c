/*
** EPITECH PROJECT, 2019
** parse_options.c
** File description:
** parsing options file.
*/

#include "options.h"

static const char *USAGE = "USAGE: ./zappy_server -p port -x width -y height\
-n name1 name2 ... -c clientsNb -f freq\n\
port        is the port number\n\
width       is the width of the world\n\
height      is the height of the world\n\
nameX       is the name of the team X\n\
clientsNb   is the number of authorized clients per team\n\
freq        is the reciprocal of time unit for execution of actions\n";

// TODO: Calculate the number of name.
options_t *create_opt(int argc, char *argv[])
{
    int flags = 0;
    int opt = 0;
    int nsecs = 0;
    int tfnd = 0;
    options_t *options = malloc(sizeof(options_t));
    options->name = malloc(sizeof(char *));

    while ((opt = getopt(argc, argv, "p:x:y:n:c:f:")) != -1) {
        switch (opt) {
            case 'p':
                options->port = atoi(optarg);
                break;
            case 'x':
                options->width = atoi(optarg);
                break;
            case 'y':
                options->height = atoi(optarg);
                break;
            case 'n':
                options->name[0] = strdup(optarg);
                break;
            case 'c':
                options->freq = atoi(optarg);
                break;
            case 'f':
            default:
                fprintf(stderr, USAGE);
                exit(84);
        }
    }
    return options;
}

int check_opt(options_t *options)
{
    return 0;
}

void print_opt(options_t *options)
{
    printf("Option {\n"
            "    port: %hd,\n"
            "    width: %d,\n"
            "    height: %d,\n"
            "    name: %s,\n"
            "    freq: %d\n"
            "}\n", options->port, options->width, options->height,
            options->name[0], options->freq);
}
