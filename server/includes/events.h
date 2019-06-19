/*
** EPITECH PROJECT, 2019
** events.h
** File description:
** Graphic event that are handled.
*/

#pragma once

#include "server.h"
#include "generic_list.h"

typedef struct event_s {
    int id;
    void *payload;
} event_t;

int add_event(server_t *server, int id, void *payload);
void handle_events(server_t *server);
