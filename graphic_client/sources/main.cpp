#include "SDL.hpp"
#include "protocols.h"
#include "Protocol.hpp"
#include "DataHandler.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>
#include <errno.h>

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
#ifdef __SWITCH__
    int sockNxlinkSock = 61;
    atexit(SDL_Quit);
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
    std::string host(argv[1]);
    int port = atoi(argv[2]);
#endif /* __SWITCH__ */
    auto protocol = Protocol(host, port);

    WindowCreator tmp("Test", 800, 600);

    auto rock_surface = SDL_LoadBMP(REALPATH("rock.bmp"));
    auto rock_texture = SDL_CreateTextureFromSurface(tmp.getRender(), rock_surface);
    
    SDL_Rect rect;
    rect.h = 200;
    rect.w = 200;
    rect.x = 200;
    rect.y = 200;

    protocol.askMapSize();


    struct Point {
        int x;
        int y;
    };

    auto dataHandler = DataHandler<Point>(protocol.getSocket(), [](int sock, Point &a) {
        pkt_header_t header;
        int ret = read(sock, &header, PKT_HDR_LEN);
        if (ret == 0 || (ret == -1 && errno != EAGAIN))
            return false;
        //std::cout << "Request: " << std::to_string(header.id) << ". [" << a << "]" << std::endl;
        if (header.id == SRV_MAP_SIZE) {
            srv_map_size_t mapSize;
            read(sock, &mapSize, SRV_MAP_SIZE_LEN);
            std::cout << "x: " << mapSize.x << " y: " << mapSize.y << std::endl;
        }
        return true;
    });

    int x = 0;
    int y = 0;
    bool done = true;
    Point point;
    SDL_GetWindowSize(tmp.getWindow(), &x, &y);
    while (done && dataHandler.handle(point)) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_JOYBUTTONDOWN:
                    if (event.jbutton.which == 0) {
                        if (event.jbutton.button == 10) {
                            done = false;
                        }
                    }
                    break;
                case SDL_FINGERMOTION:
                    rect.x = event.tfinger.x * x;
                    rect.y = event.tfinger.y * y;
                default:
                    break;
            }
        }
        SDL_RenderClear(tmp.getRender());
        SDL_RenderCopy(tmp.getRender(), rock_texture, NULL, &rect);
        SDL_RenderPresent(tmp.getRender());
    }

    SDL_DestroyRenderer(tmp.getRender());
    SDL_DestroyWindow(tmp.getWindow());
    SDL_Quit();
#ifdef __SWITCH__
    exitNxLink(sockNxlinkSock);
#endif
    std::cout << "return 0" << std::endl;
    return (0);
}
#endif /* TEST */
