#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdio>

extern "C"{
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
}

#include <QApplication>
#include <QWidget>



int main(int argc, char* argv[]) 
{

    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("My Qt App");
    window.resize(250, 150);
    window.show();
    return app.exec();

    // unsigned codecVer = avcodec_version();
    // int ver_major,ver_minor,ver_micro;
    // ver_major = (codecVer>>16)&0xff;
    // ver_minor = (codecVer>>8)&0xff;
    // ver_micro = (codecVer)&0xff;
    // SDL_Log("avcodec version is: %d=%d.%d.%d\n",codecVer,ver_major,ver_minor,ver_micro);
    // printf("123456");
    // if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    // {
    //     std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    //     return 1;
    // }

    // SDL_Window* window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    // if (!window) {
    //     std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     return 1;
    // }

    // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // if (!renderer) {
    //     std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return 1;
    // }

    // if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    //     std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
    //     SDL_DestroyRenderer(renderer);
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return 1;
    // }

    // SDL_Surface* surface = IMG_Load("C:/Users/foloheart/Pictures/Screenshots/image.png");
    // if (!surface) {
    //     std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    //     IMG_Quit();
    //     SDL_DestroyRenderer(renderer);
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return 1;
    // }

    // SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    // SDL_FreeSurface(surface);
    // if (!texture) {
    //     std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    //     IMG_Quit();
    //     SDL_DestroyRenderer(renderer);
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return 1;
    // }

    // bool quit = false;
    // SDL_Event event;
    // while (!quit) {
    //     while (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_QUIT) {
    //             quit = true;
    //         }
    //     }

    //     SDL_RenderClear(renderer);
    //     SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    //     SDL_RenderPresent(renderer);
    // }

    // SDL_DestroyTexture(texture);
    // IMG_Quit();
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();

    // return 0;
}
