#pragma once

#include <string>
#include <ctime>
#include <SDL.h>

#include "../Assets.h"
#include "Sprite.h"

class Animation : public Sprite{
public:
	int frame = 0, fps = 60, frames = 60; // frame tells what the current frame is, fps tells how many frames per second
	Assets* assets; // To grab the preloaded textures
	std::string texID; // What are the texture's id in assets?
	std::clock_t timer; //To help keep track of milliseconds since last frame switch :D
	int overall; //Combine all time to keep everything balanced, like all things should be
	int timepertick = 33; // How long does the timer have until we update the frame

	Animation(std::string texid, int framess, int fpss, Assets* ass);

	void setFrame(int f);
	void setTexID(std::string id);
	void setFPS(int f);

	//Sprite Shit
	virtual void render(SDL_Renderer*);
	virtual void render(SDL_Renderer*, int, int);
	virtual void render(SDL_Renderer*, int, int, bool);
	virtual void renderWithBounds(SDL_Renderer*);

	//Lua Compat
	virtual void lua_render(void*, int, int);
	virtual void lua_renderFlip(void*, int, int, bool);
	virtual void lua_renderDefault(void*);

private:

};

