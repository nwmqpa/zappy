/*
** EPITECH PROJECT, 2019
** server.h
** File description:
** server header file.
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include "client.h"
#include "options.h"
#include "generic_list.h"
#include "map.h"
#include "protocols.h"

/// \brief The team struct
///
/// The team struct
/// contain the name
/// the eggs linked to team
/// the clients linked to team
typedef struct team_s {
    char *name;
    list_t *clients;
    list_t *eggs;
} team_t;

int check_free_space(team_t *team);

/// The main server struct that contain all data needed by the server to run.
/// list of ia
/// list of events
/// list of graphic_client
/// the map
/// the handler register
/// the epoll sockets
/// the width and height of the server
typedef struct server_s {
    unsigned int width;
    unsigned int height;
    int epoll_fd_client;
    int epoll_fd_graphic;
    int socket_client;
    int socket_graphic;
    int freq;
    team_t **teams;
    list_t *clients;
    list_t *graphic_clients;
    int client_per_team;
    map_t *map;
    phr_t reg;
    list_t *events;
} server_t;

/// An data struct to pass through void *
typedef struct time_server_s {
    double elapsed;
    server_t *server;
} time_server_t;

// Create server and initiliaze it from options.
server_t *create_server(options_t *options);

int create_client_listener(options_t *options);
int create_graphic_listener(options_t *options);

team_t *get_ia_team(ia_t *client, server_t *server);

int add_ia_to_team(server_t *server, ia_t *client, const char *team);
void remove_client_from_team(team_t *team, ia_t *client, server_t *server);

void print_server(server_t *server);

/* DEBUG */

typedef void (*debug_func) (server_t *);

/// Data struct to pass through void *
struct server_part_s {
    char *name;
    debug_func func;
};

char *server_status(server_t *server, const char *command);

void get_info_player(void *player, const void *nothing);
void get_players_status(server_t *server);
void get_map_status(server_t *server);
void get_teams_status(server_t *server);

int count_unused_slots(team_t *team, int nb_client);

void respawn_ressources(map_t *map, server_t *server);

#endif /* SERVER_H_ */
