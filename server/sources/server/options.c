/*
** EPITECH PROJECT, 2019
** parse_options.c
** File description:
** parsing options file.
*/

#include "logger.h"
#include "options.h"

static const char *USAGE = "USAGE: ./zappy_server -p port -x width -y height\
-n name1 name2 ... -c clientsNb -f freq\n\
port        is the port number\n\
width       is the width of the world\n\
height      is the height of the world\n\
nameX       is the name of the team X\n\
clientsNb   is the number of authorized clients per team\n\
freq        is the reciprocal of time unit for execution of actions\n";

static inline int count_name(int argc, char *argv[])
{
    int i = 0;

    for (int oldind = optind - 1;
            argc != oldind && argv[oldind][0] != '-'; oldind++)
        i++;
    return i;
}

static int get_names(options_t *options, int argc, char *argv[])
{
    int i = count_name(argc, argv);

    options->name = malloc(sizeof(char *) * (i + 1));
    if (!options->name)
        return -1;
    i = 0;
    for (int oldind = optind - 1;
            argc != oldind && argv[oldind][0] != '-'; oldind++) {
        options->name[i] = strdup(argv[oldind]);
        if (!options->name[i]) {
            free(options->name);
            options->name = NULL;
            return -1;
        }
        i++;
    }
    options->name[i] = 0;
    return 0;
}

static void opt_loop(char opt, options_t *options, int argc, char *argv[])
{
    switch (opt) {
        case 'p':
            BREAK(options->port = atoi(optarg));
        case 'x':
            BREAK(options->width = atoi(optarg));
        case 'y':
            BREAK(options->height = atoi(optarg));
        case 'n':
            BREAK(get_names(options, argc, argv));
        case 'c':
            BREAK(options->client_nb = atoi(optarg));
        case 'f':
            BREAK(options->freq = atoi(optarg));
        default:
            fprintf(stderr, "%s", USAGE);
            exit(84);
    }
}

options_t *create_opt(int argc, char *argv[])
{
    int opt = 0;
    options_t *options = calloc(sizeof(options_t), 1);
    if (!options)
        return NULL;
    while ((opt = getopt(argc, argv, "p:x:y:n:c:f:")) != -1)
        opt_loop(opt, options, argc, argv);
    if (options->freq == 0)
        options->freq = 100;
    return options;
}

int check_opt(options_t *options)
{
    if (options->width > 30 || options->width < 1) {
        errorl("Invalid width.");
        return -1;
    } else if (options->height > 30 || options->height < 1) {
        errorl("Invalid height.");
        return -1;
    } else if (options->freq <= 0) {
        errorl("Invalid frequence.");
        return -1;
    } else if (options->client_nb < 0) {
        errorl("Invalid client_nb.");
        return -1;
    } else if (options->name == NULL) {
        errorl("Invalid team name");
        return -1;
    }
    return 0;
}
