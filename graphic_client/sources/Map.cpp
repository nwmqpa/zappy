/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Map.hpp"

Map::Map()
{
    getSize();
    generateMap();
}

Map::~Map()
{}

void Map::getSize()
{
    _map_size = getMapsrv();

    return (_map_size != 0);
    /*Récupération de la taille de la carte*/
}

void Map::generateMap()
{
    try {
        for (unsigned int i = 0; i < (_map_size->x * _map_size->y); i += 1) {
            /*Récupération de la composition des chaque case (srv_tile_content_t)*/
            //srv_tile_content_t *tmp = &case;
            if (_map.size() > 0 && _map[i]->getTile() != tmp)
                _map[i]->setTile(tmp);
            else
                _map.push_back(new Case(tmp, _screen));
        }
    } catch (std::exception *error) {
        _isAlive = false;
    }
    /*Génération et update des informations des cases de la carte*/
}

void Map::getMapFromServer()
{
    SOCKET sock;
    SOCKADDR_IN sin;

    //Connection socket et paramétrage
    //Besoin de mettre les packets dans la config ?
    //
    //Récupération des données avec recv et parsing des données récupérés

    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    if (connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR) {
        printf("Connecté à %s.\nPort: %d.\n", inet_ntoa(sin.sin_addr),
                htons(sin.sin_port));
        if (recv(sock, buffer, 256, 0) != SOCKET_ERROR)
            printf("Reçu: %s.\n", buffer);
    } else
        printf("Erreur lors de la connetion.\n");
    closesocket(sock);
}
