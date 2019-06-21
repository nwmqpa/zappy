#include "Window.hpp"
#include "Game.hpp"
#include "protocols.h"
#include "Protocol.hpp"
#include "DataHandler.hpp"

#ifdef __SWITCH__
#   include <switch.h>
#endif /* __SWITCH__ */

#ifdef __SWITCH__
static void initNxLink(int &sockNxlinkSock)
{
    if (R_FAILED(socketInitializeDefault()))
        return;
    sockNxlinkSock = nxlinkStdio();
    if (sockNxlinkSock >= 0)
        std::cout << "printf output now goes to nxlink server\n" << std::endl;
    else
        socketExit();
}

static void exitNxLink(int &sockNxlinkSock)
{
    if (sockNxlinkSock >= 0) {
        close(sockNxlinkSock);
        socketExit();
        sockNxlinkSock = -1;
    }
}

static void initRomFS(void) {
    Result rc = romfsInit();
    if (R_FAILED(rc)) {
        std::cout << "romfsInit: " << rc << std::endl;
        exit(0);
    } else
        std::cout << "romfsInit: sucess" << std::endl;
}

static void initJoycons(void) {
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
int main(int argc, char *argv[])
{
    std::string host("192.168.43.129");
    int port = 13334;
#ifdef __SWITCH__
    int sockNxlinkSock = -1;
    initNxLink(sockNxlinkSock);
    initRomFS();
    initJoycons();
#endif /* __SWITCH__ */
    if (argc == 3) {
        host = std::string(argv[1]);
        port = atoi(argv[2]);
    } else
        return (0);
    auto name = std::string("window");
    auto window = Window(name, 1280, 720);
    auto game = Game(host, port);
    game.life(window);
    std::cout << "Finished program." << std::endl;
#ifdef __SWITCH__
    SDL_Quit();
    exitNxLink(sockNxlinkSock);
#endif
    return (0);
}
#endif /* TEST */
