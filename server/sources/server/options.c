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

// TODO: Fix coding style.
options_t *create_opt(int argc, char *argv[])
{
    int opt = 0;
    options_t *options = calloc(sizeof(options_t), 1);
    if (!options)
        return NULL;
    while ((opt = getopt(argc, argv, "p:x:y:n:c:f:")) != -1) {
        switch (opt) {
            case 'p':
                options->port = atoi(optarg);
                break;
            case 'x':
                options->width = atoi(optarg);
                break; case 'y':
                options->height = atoi(optarg);
                break;
            case 'n':
                get_names(options, argc, argv);
                break;
            case 'c':
                options->client_nb = atoi(optarg);
                break;
            case 'f':
                options->freq = atoi(optarg);
                break;
            default:
                fprintf(stderr, USAGE);
                exit(84);
        }
    }
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

void print_opt(options_t *options)
{
    printf("Option {\n"
            "    port: %hd,\n"
            "    width: %d,\n"
            "    height: %d,\n"
            "    name: [", options->port, options->width, options->height);
    for (int i = 0; options->name[i]; i++)
        printf("%s%s", options->name[i], options->name[i + 1] ? ", " : "]\n" );
    printf("    client_nb: %d\n"
            "    freq: %d\n"
            "}\n", options->client_nb, options->freq);
}
