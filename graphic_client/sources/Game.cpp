/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include <tuple>
#include <vector>
#include "DataHandler.hpp"
#include "Protocol.hpp"
#include "Game.hpp"
#include "Utils.hpp"

static const std::vector<std::tuple<GRAPHIC_PACKETS_FROM_SERVER, std::string>> NAMES = {
	std::make_tuple(SRV_MAP_SIZE, std::string("SRV_MAP_SIZE")),
	std::make_tuple(SRV_TILE_CONTENT, std::string("SRV_TILE_CONTENT")),
	std::make_tuple(SRV_TEAMS_NAMES, std::string("SRV_TEAMS_NAMES")),
	std::make_tuple(SRV_NEW_PLAYER_CONNECT, std::string("SRV_NEW_PLAYER_CONNECT")),
	std::make_tuple(SRV_PLAYER_POSITION, std::string("SRV_PLAYER_POSITION")),
	std::make_tuple(SRV_PLAYER_LEVEL, std::string("SRV_PLAYER_LEVEL")),
	std::make_tuple(SRV_PLAYER_INVENTORY, std::string("SRV_PLAYER_INVENTORY")),
	std::make_tuple(SRV_EXPULSION, std::string("SRV_EXPULSION")),
	std::make_tuple(SRV_BROADCAST, std::string("SRV_BROADCAST")),
	std::make_tuple(SRV_INCANTATION_START, std::string("SRV_INCANTATION_START")),
	std::make_tuple(SRV_INCANTATION_END, std::string("SRV_INCANTATION_END")),
	std::make_tuple(SRV_EGG_LAYING, std::string("SRV_EGG_LAYING")),
	std::make_tuple(SRV_RESOURCE_DROP, std::string("SRV_RESOURCE_DROP")),
	std::make_tuple(SRV_RESOURCE_COLLECT, std::string("SRV_RESOURCE_COLLECT")),
	std::make_tuple(SRV_PLAYER_DEATH, std::string("SRV_PLAYER_DEATH")),
	std::make_tuple(SRV_EGG_LAYED, std::string("SRV_EGG_LAYED")),
	std::make_tuple(SRV_EGG_HATCHING, std::string("SRV_EGG_HATCHING")),
	std::make_tuple(SRV_PLAYER_CONNECT_EGG, std::string("SRV_PLAYER_CONNECT_EGG")),
	std::make_tuple(SRV_PLAYER_DEATH_EGG, std::string("SRV_PLAYER_DEATH_EGG")),
	std::make_tuple(SRV_TIME_UNIT_REQUEST, std::string("SRV_TIME_UNIT_REQUEST")),
	std::make_tuple(SRV_TIME_UNIT_CHANGE, std::string("SRV_TIME_UNIT_CHANGE")),
	std::make_tuple(SRV_END_GAME, std::string("SRV_END_GAME")),
	std::make_tuple(SRV_MESSAGE_FROM_SRV, std::string("SRV_MESSAGE_FROM_SRV")),
	std::make_tuple(SRV_UNKNOWN_COMMAND, std::string("SRV_UNKNOWN_COMMAND")),
	std::make_tuple(SRV_COMMAND_PARAMETER, std::string("SRV_COMMAND_PARAMETER")),
};

void gotMapSize(GameState &state, WindowCreator &window)
{
    if (state.tileList.empty()) {
        std::string path = "back.bmp";
        srv_map_size_t *packet = (srv_map_size_t *) state.lastData;
        std::cout << "Map size: (" << packet->x << ", "
            << packet->y << ")" << std::endl;
        state.mapSize = packet;
        for (unsigned int i = 0; i < (packet->x * packet->y); i += 1)
            state.tileList.push_back(new Tile(path, window.getRender()));
    }
}

void gotTileContent(GameState &state, WindowCreator &window)
{
    srv_tile_content_t *packet = (srv_tile_content_t *) state.lastData;
    std::cout << "Tile: (" << packet->x << ", " << packet->y << ") data" << std::endl;
    std::vector<Tile *>::iterator it = state.tileList.begin();

    if (!state.tileList.empty() && state.mapSize != NULL) {
        for (; it != state.tileList.end(); it++) {
            if (packet != (*it)->getTileInfo() && (*it)->getPosX() == packet->x
                    && (*it)->getPosY() == packet->y)
                (*it)->setTileContent(packet);
        }
        window.drawTile(state.tileList, state.mapSize);
    }
}

static const std::vector<std::tuple<GRAPHIC_PACKETS_FROM_SERVER, data_processor_t>> DATA_PROCESSORS = {
	std::make_tuple(SRV_MAP_SIZE, &gotMapSize),
	std::make_tuple(SRV_TILE_CONTENT, &gotTileContent),
	std::make_tuple(SRV_TEAMS_NAMES, nullptr),
	std::make_tuple(SRV_NEW_PLAYER_CONNECT, nullptr),
	std::make_tuple(SRV_PLAYER_POSITION, nullptr),
	std::make_tuple(SRV_PLAYER_LEVEL, nullptr),
	std::make_tuple(SRV_PLAYER_INVENTORY, nullptr),
	std::make_tuple(SRV_EXPULSION, nullptr),
	std::make_tuple(SRV_BROADCAST, nullptr),
	std::make_tuple(SRV_INCANTATION_START, nullptr),
	std::make_tuple(SRV_INCANTATION_END, nullptr),
	std::make_tuple(SRV_EGG_LAYING, nullptr),
	std::make_tuple(SRV_RESOURCE_DROP, nullptr),
	std::make_tuple(SRV_RESOURCE_COLLECT, nullptr),
	std::make_tuple(SRV_PLAYER_DEATH, nullptr),
	std::make_tuple(SRV_EGG_LAYED, nullptr),
	std::make_tuple(SRV_EGG_HATCHING, nullptr),
	std::make_tuple(SRV_PLAYER_CONNECT_EGG, nullptr),
	std::make_tuple(SRV_PLAYER_DEATH_EGG, nullptr),
	std::make_tuple(SRV_TIME_UNIT_REQUEST, nullptr),
	std::make_tuple(SRV_TIME_UNIT_CHANGE, nullptr),
	std::make_tuple(SRV_END_GAME, nullptr),
	std::make_tuple(SRV_MESSAGE_FROM_SRV, nullptr),
	std::make_tuple(SRV_UNKNOWN_COMMAND, nullptr),
	std::make_tuple(SRV_COMMAND_PARAMETER, nullptr),
};

Game::Game(std::string &ip, int port)
 : ip(ip)
 , port(port)
{
    memset(&this->state, 0, sizeof(this->state));
    this->state.isActive = true;
}

void Game::life(WindowCreator &window)
{
    auto protocol = Protocol(ip, port);
    auto dataHandler = DataHandler<GameState>(protocol.getSocket(), [](int sock, GameState &state) {
        free(state.lastData);
        memset(&state, 0, sizeof(state.lastData) + sizeof(state.lastHeader));
        pkt_header_t header;
        int ret = read(sock, &header, PKT_HDR_LEN);
        if (ret == -1 && errno == EAGAIN)
            return true;
        if (ret == 0 || (ret == -1 && errno != EAGAIN))
            return false;
        auto id = (GRAPHIC_PACKETS_FROM_SERVER) header.id;
        std::cout << "Got " << getValueForIndex<GRAPHIC_PACKETS_FROM_SERVER, std::string>(id, NAMES);
        std::cout << " of len " << std::to_string(header.size) << std::endl;
        state.lastData = calloc(1, header.size);
        ret = read(sock, &state.lastData, header.size);
        if (ret == -1 && errno == EAGAIN)
            return true;
        if (ret == 0 || (ret == -1 && errno != EAGAIN))
            return false;
        return true;
    });

    std::vector<Tile *>::iterator it = state.tileList.begin();
    while (this->state.isActive && dataHandler.handle(state)) {
        window.clearScreen();
        if (!this->state.mapRequest)
            protocol.askMapSize();
        else if (this->state.mapRequest && this->state.mapSize == NULL) {
            for (unsigned int x, y; it != state.tileList.end(); it++) {
                if (x > state.mapSize->x) {
                    x = 0;
                    y += 1;
                }
                protocol.askTileContent(x, y);
            }
        }
        this->processData(window);
        this->eventLoop(window, state.tileList);
        window.PresentScreen();
        it = state.tileList.begin();
    }
    window.destroyer();
   /* SDL_DestroyRenderer(window.getRender());
    SDL_DestroyWindow(window.getWindow());
    SDL_Quit();*/
}

void Game::processData(WindowCreator &window)
{
    if (state.lastData != nullptr) {
        auto id = (GRAPHIC_PACKETS_FROM_SERVER) state.lastHeader.id;
        auto processor = getValueForIndex<GRAPHIC_PACKETS_FROM_SERVER, data_processor_t>(id, DATA_PROCESSORS);

        if (processor != nullptr)
            processor(state, window);
    }
}

void Game::eventLoop(WindowCreator &window, std::vector<Tile *> tileList)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_JOYBUTTONDOWN:
                if (event.jbutton.which == 0) {
                    if (event.jbutton.button == 10) {
                        state.isActive = false;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    state.isActive = false;
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    window.addY(10, tileList);
                    std::cout << "X: " << window.getX() << "Y: " << window.getY() << std::endl;
                } else if (event.key.keysym.sym == SDLK_UP) {
                    window.addY(-10, tileList);
                    std::cout << "X: " << window.getX() << "Y: " << window.getY() << std::endl;
                } else if (event.key.keysym.sym == SDLK_LEFT) {
                    window.addX(-10, tileList);
                    std::cout << "X: " << window.getX() << "Y: " << window.getY() << std::endl;
                } else if (event.key.keysym.sym == SDLK_RIGHT) {
                    window.addX(10, tileList);
                    std::cout << "X: " << window.getX() << "Y: " << window.getY() << std::endl;
                }
                break;
            case SDL_QUIT:
                state.isActive = false;
                break;
            default:
                break;
        }
    }
}