/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Game.hpp"
#include "DataHandler.hpp"
#include "InputHandler.hpp"
#include "Protocol.hpp"
#include "Utils.hpp"
#include <tuple>
#include <vector>

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

Game::Game(std::string ip, int port)
    : state(ip, port)
{
    this->state.isActive = true;
}

void gotMapSize(GameState& state, Window& window)
{
    if (state.tileList.empty()) {
        std::string path = REALPATH("grass.bmp");
        auto* packet = (srv_map_size_t*)state.lastData;
        std::cout << "Map size: (" << packet->x << ", " << packet->y << ")" << std::endl;
        state.mapSize = *packet;
        for (auto elem : state.tileList)
            delete elem;
        state.tileList = std::vector<Tile*>(0);

        unsigned int count = (packet->x * packet->y);
        for (unsigned int i = 0; i < count; i += 1)
            state.tileList.push_back(new Tile(path, window.getRender()));
        state.protocol.askMapContent();
    }
}

void gotTileContent(GameState& state, Window& window)
{
    auto* packet = (srv_tile_content_t*)state.lastData;
    size_t pos = (packet->y * state.mapSize.x) + packet->x;
    std::vector<int> temp(0);
    std::cout << "Tile: (" << packet->x << ", " << packet->y << ") data" << std::endl;

    temp.push_back(packet->q0);
    temp.push_back(packet->q1);
    temp.push_back(packet->q2);
    temp.push_back(packet->q3);
    temp.push_back(packet->q4);
    temp.push_back(packet->q5);
    temp.push_back(packet->q6);
    state.tileList.at(pos)->setTileContent(packet->x, packet->y, temp, packet->players);
}

void gotNewPlayerConnect(GameState& state, Window& window)
{
    auto* packet = (srv_new_player_connect_t*)state.lastData;
    std::string path = REALPATH("player.bmp");
    Player* temp = new Player(path, window.getRender());

    temp->setPosition(packet->x, packet->y);
    temp->setPlayerNum(packet->player_num);
    temp->setOrientation(packet->orientation);
    temp->setTeamName(std::string(packet->team_name));
    state.playerList.push_back(temp);
}

void gotPlayerPosition(GameState& state, Window& window)
{
    auto* packet = (srv_player_pos_t*)state.lastData;

    for (auto elem : state.playerList) {
        if (elem->getPlayerNum() == packet->player_num) {
            elem->setPosition(packet->x, packet->y);
        }
    }
}

void gotPlayerLevel(GameState& state, Window& window)
{
    auto* packet = (srv_player_level_t*)state.lastData;

    for (auto elem : state.playerList) {
        if (elem->getPlayerNum() == packet->player_num) {
            elem->setLevel(packet->level);
        }
    }
}

static const std::vector<std::tuple<GRAPHIC_PACKETS_FROM_SERVER, data_processor_t>> DATA_PROCESSORS = {
    std::make_tuple(SRV_MAP_SIZE, &gotMapSize),
    std::make_tuple(SRV_TILE_CONTENT, &gotTileContent),
    std::make_tuple(SRV_TEAMS_NAMES, nullptr),
    std::make_tuple(SRV_NEW_PLAYER_CONNECT, &gotNewPlayerConnect),
    std::make_tuple(SRV_PLAYER_POSITION, &gotPlayerPosition),
    std::make_tuple(SRV_PLAYER_LEVEL, &gotPlayerLevel),
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

void Game::life(Window& window)
{
    auto dataHandler = DataHandler<GameState>(state.protocol.getSocket(),
        [](int sock, GameState& state) {
            free(state.lastData);
            state.lastData = nullptr;
            state.lastHeader = {};
            pkt_header_t header;
            int ret = read(sock, &header, PKT_HDR_LEN);
            if (ret == -1 && errno == EAGAIN)
                return true;
            if (ret == 0 || (ret == -1 && errno != EAGAIN))
                return false;
            auto id = (GRAPHIC_PACKETS_FROM_SERVER)header.id;
            state.lastData = calloc(1, header.size);
            state.lastHeader = header;
            ret = read(sock, state.lastData, header.size);
            if (ret == -1 && errno == EAGAIN)
                return true;
            if (ret == 0 || (ret == -1 && errno != EAGAIN))
                return false;
            return true;
        });

    state.protocol.askMapSize();
    InputHandler input;
    InputHandler::InputDatas inputData;

    while (this->state.isActive && dataHandler.handle(state)) {
        this->limitFramerate();
        this->processData(window);
        window.clearScreen();
        input.handle(window, inputData);
        this->updateCamera(inputData);
        state.isActive = !inputData.should_quit;
        window.render(state, state.mapSize.x, state.mapSize.y);
        window.renderPlayer(state);
        window.presentScreen();
        inputData.x = 0;
        inputData.y = 0;
        inputData.zoom = 0;
    }
}

void Game::limitFramerate() noexcept
{
    unsigned int startTime = 0;
    unsigned int endTime = 0;
    unsigned int delta = 0;
    short fps = 60;
    short timePerFrame = 16;

    if (!startTime)
        startTime = SDL_GetTicks();
    else
        delta = endTime - startTime;

    if (delta < timePerFrame) {
        SDL_Delay(timePerFrame - delta);
    }

    // if delta is bigger than 16ms between frames, get the actual fps
    if (delta > timePerFrame) {
        fps = 1000 / delta;
    }

    printf("FPS is: %i \n", fps);

    startTime = endTime;
    endTime = SDL_GetTicks();
    SDL_Delay(1000 / maxFPS - SDL_GetTicks() + previousTime);
}

void Game::updateCamera(InputHandler::InputDatas& inputData)
{
    state.camera.center.x *= state.camera.scale.x;
    state.camera.center.y *= state.camera.scale.y;
    state.camera.center.x += inputData.x;
    state.camera.center.y += inputData.y;
    state.camera.scale.x += inputData.zoom;
    state.camera.scale.y += inputData.zoom;
    if (state.camera.scale.y < 0.5) {
        state.camera.scale.x = 0.5;
        state.camera.scale.y = 0.5;
    }
    if (state.camera.scale.y > 5) {
        state.camera.scale.x = 5;
        state.camera.scale.y = 5;
    }
    state.camera.center.x /= state.camera.scale.x;
    state.camera.center.y /= state.camera.scale.y;
}

void Game::processData(Window& window)
{
    if (state.lastData != nullptr) {
        auto id = (GRAPHIC_PACKETS_FROM_SERVER)state.lastHeader.id;
        auto processor = getValueForIndex<GRAPHIC_PACKETS_FROM_SERVER, data_processor_t>(id, DATA_PROCESSORS);

        if (processor != nullptr)
            processor(state, window);
        else
            std::cerr << "Handler not found." << std::endl;
    }
}
