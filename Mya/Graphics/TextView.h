#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "Font.h"
#include "Texture.h"
#include "../Mya.h"

class TextView {
public:
	int x, y;
	TextView(Font, std::string, int, int, SDL_Renderer*);
	TextView(Font, std::string, int, int, void*);

	void render(SDL_Renderer*);
	void render(SDL_Renderer*, int, int);
	void lua_render(void*);
	void lua_renderWH(void*, int, int);
	void setXY(int,int);
	void setColor(SDL_Color);
	void setColorInt(void*, Uint8, Uint8, Uint8);
	SDL_Color getColor();
	void setText(std::string, SDL_Renderer*);
	void lua_setText(std::string, void*);
	std::string getText();

	int getWidth();
	int getHeight();

	Texture tex;
	std::string text;
	Font font;
	SDL_Color color;

	void update(SDL_Renderer*);
	void setFont(Font, SDL_Renderer*);
	void lua_setFont(Font, void*);
};