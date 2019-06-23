/*
** EPITECH PROJECT, 2019
** zappy.h
** File description:
** zappy header file.
*/

#ifndef ZAPPY_H_
#define ZAPPY_H_

#include "server.h"
#include "options.h"

/// \mainpage Zappy documentation
///
/// \section intro_sec Documentation
///
/// This is the Zappy full documentation.
///
/// \section install_sec Architecture
///
/// The Zappy server handle 2 type of clients.
/// - Client Player
/// - Client Graphic
///
/// - Async
/// The difficulty of the server is to bring asyncronous handlers in
/// mono-threaded code, and with blocking TCP/IP.
///
/// - Time
/// All the Zappy game is working with a Time mesure.
/// (Players's time to live, Players's needs, Players's commands cooldown)
/// And the time is based on real time (real_time / freq).
///
/// To make everything work we work a lot on the server architecture.
///
/// First: The time is handled by getting the time elapsed since
/// the last iteration.
/// then multiplied by the frequency and removed from all timed entities.
///
/// Then: The connexion with the two clients are handled by `epoll`
/// more efficient
/// than `select`. We use a dispatching system with 3 function pointer:
///     - on_connect (Handle the behaviour of a client connection.)
///     - on_disconect ( // )
///     - on_active (Handle a client incomming message.)
/// So the logic of the two clients are separated by two dispatchers.
/// `graphic_dispatcher()` and `client_dispatcher()`
///
/// And:
/// A generic chained list system (`list_t`) as been built at the begin of
/// the project to
/// let us use `functional` type of programming when we needed it.
///
/// \subsection Players (IA)
///
/// on_connect: Player connect choose a team and is added to map and the
///              choosen team.
///
/// on_disconect: Player is removed from the server when he die or when he quit.
///
/// on_active: Player input is checked and cooldown begin until the end then the
///            asked command is executed.
///
/// \subsection Client Graphic
///
/// The graphic client have two types of events:
///     - Request: srv_tile_content... client ask to the server.
///     - Events: srv_new_player... server send event that the client cannot
///               know.
///
///

int zappy_server(server_t *server);

#endif /* ZAPPY_H_ */
