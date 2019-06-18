/*
** EPITECH PROJECT, 2019
** Protocol.cpp
** File description:
** Protocole implementation.
*/

#include "Protocol.hpp"

void Protocol::setupSocket() {
    int ret = 0;
    struct sockaddr_in data = {0};

    data.sin_family = AF_INET;
    data.sin_port = htons(_port);
    data.sin_addr.s_addr = inet_addr(_ip.c_str());
    ret = connect(_sock, (struct sockaddr *) &data, sizeof(struct sockaddr));
    if (ret == -1) {
        std::cerr << "Error cannot connect socket." << std::endl;
        exit(84);
    }
}

Protocol::Protocol(std::string ip, short int port) noexcept
    : _port(port)
    , _ip(ip)
    , _sock(0)
{
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock == -1) {
        std::cout << "Error cannot create the socket." << std::endl;
        exit(84);
    }
    struct hostent *host = gethostbyname(ip.c_str());
    _ip = std::string(inet_ntoa(*(struct in_addr *)(host->h_addr_list[0])));
    this->setupSocket();
}

bool Protocol::askMapSize() const noexcept {
    struct {
        pkt_header_t header;
        clt_map_size_t paylaod;
    } ask = {
        {   .id = CLT_MAP_SIZE,
            .version = PROTOCOL_VERSION,
            .size = CLT_MAP_SIZE_LEN,
            .subid = 0 },
        { 0 }
    };
    std::cout << "Asking for map size." << std::endl;
    return write(_sock, &ask, PKT_HDR_LEN + CLT_MAP_SIZE_LEN) == -1;
}

bool Protocol::askMapContent() const noexcept {
    struct {
        pkt_header_t header;
        clt_map_content_t paylaod;
    } ask = {
        {   .id = CLT_MAP_CONTENT,
            .version = PROTOCOL_VERSION,
            .size = CLT_MAP_CONTENT_LEN,
            .subid = 0 },
        { 0 }
    };

    return write(_sock, &ask, PKT_HDR_LEN + CLT_MAP_CONTENT_LEN) == -1;
}

bool Protocol::askTileContent(unsigned int x, unsigned int y) const noexcept {
    struct {
        pkt_header_t header;
        clt_tile_content_t paylaod;
    } ask = {
        {   .id = CLT_TILE_CONTENT,
            .version = PROTOCOL_VERSION,
            .size = CLT_TILE_CONTENT_LEN,
            .subid = 0 },
        { .x = x, .y = y }
    };

    return write(_sock, &ask, PKT_HDR_LEN + CLT_TILE_CONTENT_LEN) == -1;
}

bool Protocol::askTeamsNames() const noexcept {
    struct {
        pkt_header_t header;
        clt_teams_names_t paylaod;
    } ask = {
        {   .id = CLT_TEAMS_NAMES,
            .version = PROTOCOL_VERSION,
            .size = CLT_TEAMS_NAMES_LEN,
            .subid = 0 },
        { 0 }
    };

    return write(_sock, &ask, PKT_HDR_LEN + CLT_TEAMS_NAMES_LEN) == -1;
}

bool Protocol::askPlayerPosition(unsigned int id) const noexcept {
    struct {
        pkt_header_t header;
        clt_player_pos_t payload;
    } ask = {
        {   .id = CLT_PLAYER_POSITION,
            .version = PROTOCOL_VERSION,
            .size = CLT_PLAYER_POS_LEN,
            .subid = 0 },
        { id }
    };

    return write(_sock, &ask, PKT_HDR_LEN + CLT_PLAYER_POS_LEN) == -1;
}

bool Protocol::askPlayerLevel(unsigned int id) const noexcept {
    struct {
        pkt_header_t header;
        clt_player_level_t paylaod;
    } ask = {
        {   .id = CLT_PLAYER_LEVEL,
            .version = PROTOCOL_VERSION,
            .size = CLT_PLAYER_LEVEL_LEN,
            .subid = 0 },
        { id }
    };

    return write(_sock, &ask, PKT_HDR_LEN + CLT_PLAYER_LEVEL_LEN) == -1;
}

bool Protocol::askPlayerInventory(unsigned int id) const noexcept {
    struct {
        pkt_header_t header;
        clt_player_inventory_t paylaod;
    } ask = {
        {   .id = CLT_PLAYER_INVENTORY,
            .version = PROTOCOL_VERSION,
            .size = CLT_PLAYER_INVENTORY_LEN,
            .subid = 0 },
        { id }
    };

    return write(_sock, &ask, PKT_HDR_LEN + CLT_PLAYER_INVENTORY_LEN) == -1;
}

bool Protocol::askTimeUnitRequest() const noexcept {
    struct {
        pkt_header_t header;
        clt_time_unit_request_t paylaod;
    } ask = {
        {   .id = CLT_TIME_UNIT_REQUEST,
            .version = PROTOCOL_VERSION,
            .size = CLT_TIME_UNIT_REQUEST_LEN,
            .subid = 0 },
        {}
    };

    return write(_sock, &ask, PKT_HDR_LEN + CLT_TIME_UNIT_REQUEST_LEN) == -1;
}

bool Protocol::askTimeUnitChange() const noexcept {
    struct {
        pkt_header_t header;
        clt_time_unit_change_t paylaod;
    } ask = {
        {   .id = CLT_TIME_UNIT_CHANGE,
            .version = PROTOCOL_VERSION,
            .size = CLT_TIME_UNIT_CHANGE_LEN,
            .subid = 0 },
        {}
    };

    return write(_sock, &ask, PKT_HDR_LEN + CLT_TIME_UNIT_CHANGE_LEN) == -1;
}
