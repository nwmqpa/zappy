/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Map.hpp"

Map::Map()
{
    map_size = getSize;
}

Map::~Map()
{
}

bool Map::getSize()
{
    pkt_header_t request;

    request.id = GRAPHIC_PACKETS_FROM_SERVER::SRV_MAP_SIZE;
    request.version = PROTOCOL_VERSION;

    /*Mise en place de la structure "Packet Handler"*/

    if (!getInfoFromServer(/*Packet Handler*/)) {
        printf("Error DataCollect: Size.\n");
        return false;
    }
    /*Récupération de la taille de la carte*/
}

bool Map::getCaseData()
{
}

void Map::UpdateCaseData()
{
    for (int caseNbr = 0; caseNbr < (map_size.x * map_size.y); caseNbr++) {
        caseData = getCaseData();
        if (map.size() == caseNbr)
            map.push_back(new Case(caseData));
        else if (caseData != map[i])
            map[i].setData(caseData);
    }
    /*Génération et update des informations des cases de la carte*/
}

void Map::getInfoFromServer(/*struct de demande de donnée(packet)*/)
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
