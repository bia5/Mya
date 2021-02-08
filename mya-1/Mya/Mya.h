#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#undef main
#include <glad/glad.h>
#include <SDL_net.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Utils/FPS.h"
#include "Utils/Timer.h"
#include "Lua/Lua.h"

class Mya {
public:
	const char* VERSION = "Mya 1.5.0 Beta (Codename: Gahyeon)";
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
	void setWindowTitle(std::string);
	void setWindowIcon(std::string tex);
	void showCursor(bool);
	int getWidth();
	int getHeight();
	std::string getPath();

	std::string getVersion();
	int getFps();
	bool getIsServer();
	void setUPS(int);
	int getUPS();

	//Lua Compat
	Mya* getMya();

private:
	SDL_Window* window;
	SDL_GLContext glContext;

	bool glRenderQuad = true;

	static bool run;
	static bool fullscreen;

	std::clock_t timer; //To help keep track of milliseconds since last update :D
	int overall; //Combine all time to keep everything balanced, like all things should be
	int timepertick = 33; // How long does the timer have until we call another update
	int ups = 60; //how many times per second to call update
};