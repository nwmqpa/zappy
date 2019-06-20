#include "WindowCreator.hpp"
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

//#ifndef TEST
int main(void/*int argc, char *argv[]*/)
{/*
#ifdef __SWITCH__
    int sockNxlinkSock = -1;
    initNxLink(sockNxlinkSock);
    initRomFS();
    initJoycons();
    std::string host("192.168.43.129");
    int port = 13334;
#else
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
        exit(84);
    }
    auto protocol = Protocol(argv[1], atoi(argv[2]));

    auto dataHandler = DataHandler<int>(protocol.getSocket(), [](int sock, int &a) {
        pkt_header_t header;
        int ret = read(sock, &header, PKT_HDR_LEN);
        if (ret == -1 && errno == EAGAIN)
            return true;
        if (ret == 0 || (ret == -1 && errno != EAGAIN))
            return false;
        std::cout << "Request: " << std::to_string(header.id) << ". [" << a << "]" << std::endl;
        tmp.setupData(header);
        if (header.id == SRV_TILE_CONTENT_LEN) {
            srv_map_size_t mapSize;
            read(sock, &mapSize, SRV_TILE_CONTENT_LEN);
            std::cout << "x: " << mapSize.x << " y: " << mapSize.y << std::endl;
            tmp.setMapSize(mapSize);
        }
        return true;
    });

    std::string title = "Zappy";
    WindowCreator tmp(title, 800, 600);
    int a = 0;

    tmp.life(dataHandler, protocol, a);
    auto rock_surface = SDL_LoadBMP(REALPATH("rock.bmp"));
    auto rock_texture = SDL_CreateTextureFromSurface(tmp.getRender(), rock_surface);

    SDL_Rect rect;
    rect.h = 200;
    rect.w = 200;
    rect.x = 200;
    rect.y = 200;
    SDL_RenderCopy(tmp.getRender(), rock_texture, NULL, &rect);

    SDL_RenderPresent(tmp.getRender());

    sleep(10);
    SDL_DestroyRenderer(tmp.getRender());
    SDL_DestroyWindow(tmp.getWindow());
    SDL_Quit();
    std::string host(argv[1]);
    int port = atoi(argv[2]);
#endif *//* __SWITCH__ *//*
    auto name = std::string("window");
    auto window = WindowCreator(name, 1280, 720);
    auto game = Game(host, port);
    game.life(window);
    std::cout << "Finished program." << std::endl;
#ifdef __SWITCH__
    SDL_Quit();
    exitNxLink(sockNxlinkSock);
#endif*/
    auto name = std::string("window");
    auto window = WindowCreator(name, 1280, 720);
    auto game = Game(name, 666);
    game.life(window);
    return (0);
}
//#endif /* TEST */
