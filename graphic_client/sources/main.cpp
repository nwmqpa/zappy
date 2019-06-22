#include "DataHandler.hpp"
#include "Game.hpp"
#include "Protocol.hpp"
#include "Window.hpp"
#include "protocols.h"

#ifdef __SWITCH__
#include <switch.h>

static void initNxLink(int& sockNxlinkSock)
{
    if (R_FAILED(socketInitializeDefault()))
        return;
    sockNxlinkSock = nxlinkStdio();
    if (sockNxlinkSock >= 0)
        std::cout << "printf output now goes to nxlink server\n"
                  << std::endl;
    else
        socketExit();
}

static void exitNxLink(int& sockNxlinkSock)
{
    if (sockNxlinkSock >= 0) {
        close(sockNxlinkSock);
        socketExit();
        sockNxlinkSock = -1;
    }
}

static void initRomFS(void)
{
    Result rc = romfsInit();
    if (R_FAILED(rc)) {
        std::cout << "romfsInit: " << rc << std::endl;
        exit(0);
    } else
        std::cout << "romfsInit: sucess" << std::endl;
}

static void initJoycons(void)
{
    for (int i = 0; i < 2; i++) {
        if (SDL_JoystickOpen(i) == NULL) {
            std::cout << "SDL_JoystickOpen: " << SDL_GetError() << std::endl;
            exit(0);
        } else {
            std::cout << "SDL_JoystickOpen: success." << std::endl;
        }
    }
}
#endif

#ifndef TEST
int main(int argc, char* argv[])
{
    std::string host("62.4.16.75");
    int port = 13334;
#ifdef __SWITCH__
    int sockNxlinkSock = -1;
    initNxLink(sockNxlinkSock);
    initRomFS();
    initJoycons();
    if (argc == 2) {
        host = std::string(argv[0]);
        port = atoi(argv[1]);
    }
#else
    if (argc == 3) {
        host = std::string(argv[1]);
        port = atoi(argv[2]);
    }
#endif /* __SWITCH__ */
    auto name = std::string("window");
    try {
        auto game = Game(host, port);
        auto window = Window(name, 1280, 720);
        game.life(window);
    } catch (const GraphicalException& e) {
        std::cout << "Error while initialization: " << e.what() << ". Quitting." << std::endl;
        return 0;
    };
#ifdef __SWITCH__
    SDL_Quit();
    exitNxLink(sockNxlinkSock);
#endif
    return (0);
}
#endif /* TEST */
