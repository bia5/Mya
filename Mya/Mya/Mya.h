#pragma once 

#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

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
    void setAppVersion(short,short,short);

    //Random SDL2 binds (for lua)
    const char getOS();
private:
    //Easy to edit variables <3
    const short VERSION_PRIMARY = 2;
    const short VERSION_SECONDARY = 0;
    const short VERSION_TERTIARY = 0;
    const std::string VERSION_CODENAME = "RIOT";
    std::string VERSION = "MYA UNDEFINED";
    std::string WINDOW_NAME = "WINDOW_NAME";
    int WINDOW_WIDTH = 640;
    int WINDOW_HEIGHT = 480;
    bool run = false;
    short APP_VERSION_PRIMARY = 1;
    short APP_VERSION_SECONDARY = 0;
    short APP_VERSION_TERTIARY = 0;

    //VULKAN VARIABLES
    SDL_Window* window;
    VkInstance instance;
};