/*
** EPITECH PROJECT, 2019
** handlers.h
** File description:
** Handlers callback header file.
*/

#pragma once

int on_connect_graphic(int socket, void *data);

int on_delete_graphic(int socket, void *data);

int on_active_graphic(int socket, void *data);

int on_connect_client(int socket, void *data);

int on_delete_client(int socket, void *data);

int on_active_client(int socket, void *data);
