#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Mya;

class Texture {
public:
	SDL_Texture* texture;
	int w = 1, h = 1;
	bool a = false;

	Texture();
	Texture(std::string, SDL_Renderer*);
	Texture(SDL_Surface*, SDL_Renderer*);

	//Lua Compat
	Texture(std::string, Mya*);

	SDL_Texture* getTexture();
	void destroy();
	int getW();
	int getH();
};