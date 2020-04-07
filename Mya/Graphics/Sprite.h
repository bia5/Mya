#pragma once

#include <SDL.h>
#include "Texture.h"

class Sprite {
public:
	float x = 0, y = 0, w = 0, h = 0;
	int outlineColor1 = 0, outlineColor2 = 0, outlineColor3 = 0, outlineColor4 = 0;
	SDL_Rect bounds;
	Texture* tex;
	bool canRRender = false;
	bool renderBounds = false;

	Sprite(Texture*);

	void setTexture(Texture*);

	void destroy();

	virtual void update();
	virtual void render(SDL_Renderer*);
	virtual void render(SDL_Renderer*, int, int);
	virtual void render(SDL_Renderer*, int, int, bool);
	virtual void renderWithBounds(SDL_Renderer*);
	void setBounds(SDL_Rect);
	SDL_Rect getBounds();
	void setAutoBounds(bool);
	void setX(float);
	void setY(float);
	int getX();
	int getY();
	void setRenderOutline(bool);
	void setOutlineColor(int, int, int, int);

	//Lua Compat
	void lua_render(void*, int, int);
	void lua_renderFlip(void*, int, int, bool);
	void lua_renderDefault(void*);
	bool isColliding(Sprite);
	bool isPointColliding(int, int);
	bool isPointInRect(float x, float y, float, float, float, float);

private:
	bool autoSetBounds = true;
};