#include "SDL.hpp"
#include "protocols.h"
#include <vector>
#include <unistd.h>
#include <iostream>

#ifdef __SWITCH__
#   include <switch.h>
#endif /* __SWITCH__ */

#ifdef __SWITCH__
void init_romFS(void) {
    Result rc = romfsInit();
    if (R_FAILED(rc)) {
        std::cout << "romfsInit: " << rc << std::endl;
        exit(0);
    } else
        std::cout << "romfsInit: sucess" << std::endl;
}

void init_joycons(void) {
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

int main(void)
{
#ifdef __SWITCH__
    atexit(SDL_Quit);
    socketInitializeDefault();
    nxlinkStdio();
    std::cout << "NXLink server ready." << std::endl;
    init_romFS();
    init_joycons();
#endif /* __SWITCH__ */
    WindowCreator tmp("Test", 800, 600);

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
    return (0);
}
