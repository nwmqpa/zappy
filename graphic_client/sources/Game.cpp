/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Game.hpp"

Game::Game(const char *ip, int port, int a)
    :ip(ip),
    port(port),
    a(a)
{
}

void Game::life(WindowCreator *window)
{
    auto protocol = Protocol(ip, port);
    auto dataHandler = DataHandler<srv_game_data_t>(protocol.getSocket(),
            [](int sock, srv_game_data_t &a) {
        pkt_header_t header;
        int ret = read(sock, &header, PKT_HDR_LEN);
        if (ret == -1 && errno == EAGAIN)
            return true;
        if (ret == 0 || (ret == -1 && errno != EAGAIN))
            return false;
        std::cout << "Request: " << std::to_string(header.id)
        << ". [" << a << "]" << std::endl;
        a.id = header.id;
        return true;
    });

    while (data.handle(data)) {
        dataSetup(protocol.getSocket(), a.id, window);
        window.display();
    }
}

void Game::dataSetup(int sock, int id, WindowCreator *window)
{
    switch (id) {
        case SRV_MAP_SIZE:
            if ((window->getTile()).empty()) {
                read(sock, &data.mapSize, SRV_TILE_CONTENT_LEN);
                window.setMapSize(&mapSize);
            }
            break;
        case SRV_TILE_CONTENT:
            break;
    }
}
