#pragma once 

#include <iostream>
#include <SDL2/SDL.h>

class Mya{
public:
    Mya();

    //Vulkan
    bool initGraphics();

    //Network
    bool initNetworkUDP();
    bool initNetworkTCP();

    //Loops
    void render();
    void update();
    void onExit();

    //ETC
    bool getRunning();
    void setWindowName(std::string _window_name);

    //Random SDL2 binds (for lua)
    const char getOS();
private:
    //Easy to edit variables <3
    const std::string VERSION = "Mya 2.0.0 Jett";
    std::string WINDOW_NAME = "WINDOW_NAME";
    int WINDOW_WIDTH = 640;
    int WINDOW_HEIGHT = 480;
    bool run = false;

    //VULKAN VARIABLES
    SDL_Window* window;
};