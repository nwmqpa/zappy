/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Game.hpp"
#include "DataHandler.hpp"
#include "InputHandler.hpp"
#include "Handlers.hpp"
#include "Protocol.hpp"
#include "Utils.hpp"
#include "ResourcesManager.hpp"
#include <tuple>
#include <vector>

Game::Game(std::string ip, int port)
    : state(ip, port)
    , endTime(0)
    , startTime(0)
    , delta(0)
    , fps(60)
    , timePerFrame(16)
{
    this->state.isActive = true;
}

void Game::loadResources(Window &window)
{
    try {
        state.resourcesManager.addResource(REALPATH("grass.bmp"), "tile", window.getRender());
        state.resourcesManager.addResource(REALPATH("deraumere.bmp"), "deraumere", window.getRender());
        state.resourcesManager.addResource(REALPATH("egg.bmp"), "egg", window.getRender());
        state.resourcesManager.addResource(REALPATH("food.bmp"), "food", window.getRender());
        state.resourcesManager.addResource(REALPATH("linemate.bmp"), "linemate", window.getRender());
        state.resourcesManager.addResource(REALPATH("mendiane.bmp"), "mendiane", window.getRender());
        state.resourcesManager.addResource(REALPATH("player.bmp"), "player", window.getRender());
        state.resourcesManager.addResource(REALPATH("sibur.bmp"), "sibur", window.getRender());
        state.resourcesManager.addResource(REALPATH("thystame.bmp"), "thystame", window.getRender());
    } catch (const GraphicalException &e) {
        std::cerr << "Cannot load resources: " << e.what() << "." << std::endl;
        exit(0);
    }
}

void Game::life(Window& window)
{
    auto dataHandler = DataHandler<GameState>(state.protocol.getSocket(), [](int sock, GameState& state) {
        pkt_header_t header;
        free(state.lastData);
        state.lastData = nullptr;
        state.lastHeader = {};
        int ret = read(sock, &header, PKT_HDR_LEN);
        if (ret == -1 && errno == EAGAIN)
            return true;
        if (ret == 0 || (ret == -1 && errno != EAGAIN))
            return false;
        state.lastData = calloc(1, header.size);
        state.lastHeader = header;
        ret = read(sock, state.lastData, header.size);
        if (ret == -1 && errno == EAGAIN)
            return true;
        if (ret == 0 || (ret == -1 && errno != EAGAIN))
            return false;
        return true;
    });
    this->loadResources(window);

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
        window.presentScreen();
        inputData.x = 0;
        inputData.y = 0;
        inputData.zoom = 0;
    }
}

void Game::limitFramerate() noexcept
{
    if (!startTime)
        startTime = SDL_GetTicks();
    else
        delta = endTime - startTime;
    if (delta < timePerFrame)
        SDL_Delay(timePerFrame - delta);
    if (delta > timePerFrame)
        fps = 1000 / delta;
    startTime = endTime;
    endTime = SDL_GetTicks();
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
        auto processor = getValueForIndex<GRAPHIC_PACKETS_FROM_SERVER, data_processor_t>(id, Handlers::HANDLERS);

        if (processor != nullptr)
            processor(state, window);
        else
            std::cerr << "Handler not found." << std::endl;
    }
}
