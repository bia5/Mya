#pragma once


#include <iostream>
#include <string>
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Utils/FPS.h"
#include "Utils/Timer.h"
#include "Assets.h"

#include "Graphics/Font.h"
#include "Graphics/TextView.h"

#include "Graphics/Sprite.h"

#include "Lua/Lua.h"

class Mya {
public:
	const char* VERSION = "Mya Web 1.5.0 Beta (Codename: Leo)";
	static Assets* assets;

	Timer deltaTimer;
	Timer trueDeltaTimer;
	float delta = 0;
	FPS fps;
	int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;
	int osw = 1280, osh = 720;
	bool isServer = false;

	TextView* tv;
	Sprite* sprite;

	Lua* lua;

	Mya();

	bool init(std::string, int, int);
	bool loop();
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
	void setIsOnTop(bool onTop);

	std::string getVersion();
	int getFps();
	bool getIsServer();
	Assets* getAssets();
	void setUPS(int);
	int getUPS();

	void deltaUpdate();
	float getDelta();

	//Lua Compat
	void* lua_getRenderer();
	Mya* getMya();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	static bool run;
	static bool fullscreen;

	std::clock_t timer; //To help keep track of milliseconds since last update :D
	int overall; //Combine all time to keep everything balanced, like all things should be
	int timepertick = 33; // How long does the timer have until we call another update
	int ups = 1; //how many times per second to call update
};