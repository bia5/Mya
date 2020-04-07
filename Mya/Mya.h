#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#undef main
#include <SDL_net.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Utils/FPS.h"
#include "Utils/Timer.h"
#include "Graphics/Assets.h"
#include "Lua/Lua.h"

class Mya {
public:
	const char* VERSION = "Mya 1.3.5 Beta (Codename: Leah)";
	static Assets* assets;
	static Lua* lua;

	Timer deltaTimer;
	FPS fps;
	int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;
	int osw = 1280, osh = 720;
	bool isServer = false;
	Mya();

	void initLua();
	bool init(std::string, int, int);
	void update();
	void render();
	void exit();
	bool isRunning();
	void close();
	void setFullscreen(bool);
	bool getFullscreen();
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	void setWindowTitle(std::string);
	void setWindowIcon(std::string tex);
	void showCursor(bool);
	int getWidth();
	int getHeight();
	std::string getPath();
	void setRenderDrawColor(int, int, int, int);

	std::string getVersion();
	int getFps();
	bool getIsServer();
	Assets* getAssets();

	//Lua Compat
	void* lua_getRenderer();
	Mya* getMya();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	static bool run;
	static bool fullscreen;
};