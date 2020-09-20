#include "Mya.h"

Mya::Mya(){
    std::cout << "Launching "+VERSION+"!\n";
    SDL_Init(SDL_INIT_EVERYTHING);
}

bool Mya::initGraphics(){
    if(SDL_Init(SDL_INIT_EVERYTHING) > -1){
        window = SDL_CreateWindow(WINDOW_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);
        if(window != NULL){
            run = true;
        }
    }
    return false;
}

void Mya::render(){}
void Mya::update(){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            run = false;
        }
    }
}

void Mya::onExit(){
    std::cout << "Mya shutting down!\n";
}

bool Mya::getRunning(){
    return run;
}

void Mya::setWindowName(std::string _window_name){
    WINDOW_NAME = _window_name;
}

const char Mya::getOS(){
    return *SDL_GetPlatform();
}