#include "TextView.h"

TextView::TextView(Font _font, std::string _string, int _x, int _y, SDL_Renderer* _renderer) {
	color = { 0, 0, 169 };
	font = _font;
	text = _string;
	x = _x;
	y = _y;
	update(_renderer);
}

TextView::TextView(Font _font, std::string _string, int _x, int _y, void* r) {
	SDL_Renderer* _renderer = (SDL_Renderer*)r;
	color = { 0, 0, 169 };
	font = _font;
	text = _string;
	x = _x;
	y = _y;
	update(_renderer);
}

void TextView::update(SDL_Renderer* r) {
	if(tex.a)
		tex.destroy();
	tex = Texture(TTF_RenderText_Solid(font.font, text.c_str(), color), r);
}

void TextView::setFont(Font f, SDL_Renderer* r)
{
	font = f;
	update(r);
}

void TextView::lua_setFont(Font f, void*r)
{
	SDL_Renderer* _renderer = (SDL_Renderer*)r;
	font = f;
	update(_renderer);
}

void TextView::render(SDL_Renderer* _renderer) {
	SDL_Rect stretchRect;
	stretchRect.x = x;
	stretchRect.y = y;
	stretchRect.w = tex.w;
	stretchRect.h = tex.h;

	if(text != "")
		SDL_RenderCopy(_renderer, tex.getTexture(), NULL, &stretchRect);
}

void TextView::render(SDL_Renderer* _renderer, int w, int h) {
	SDL_Rect stretchRect;
	stretchRect.x = x;
	stretchRect.y = y;
	stretchRect.w = w;
	stretchRect.h = h;

	if (text != "")
		SDL_RenderCopy(_renderer, tex.getTexture(), NULL, &stretchRect);
}

void TextView::lua_render(void* r) {
	SDL_Renderer* _renderer = (SDL_Renderer*)r;

	SDL_Rect stretchRect;
	stretchRect.x = x;
	stretchRect.y = y;
	stretchRect.w = tex.w;
	stretchRect.h = tex.h;

	if (text != "")
		SDL_RenderCopy(_renderer, tex.getTexture(), NULL, &stretchRect);
}

void TextView::lua_renderWH(void* r, int w, int h) {
	SDL_Renderer* _renderer = (SDL_Renderer*)r;

	SDL_Rect stretchRect;
	stretchRect.x = x;
	stretchRect.y = y;
	stretchRect.w = w;
	stretchRect.h = h;

	if (text != "")
		SDL_RenderCopy(_renderer, tex.getTexture(), NULL, &stretchRect);
}

void TextView::setXY(int xx, int yy)
{
	x = xx;
	y = yy;
}

void TextView::setColor(SDL_Color c) {
	color = c;
}

void TextView::setColorInt(void* rr, Uint8 r, Uint8 g, Uint8 b) {
	SDL_Renderer* rrr = (SDL_Renderer*)rr;
	color = { r,g,b };
	update(rrr);
}

SDL_Color TextView::getColor()
{
	return color;
}

void TextView::setText(std::string s, SDL_Renderer* r) {
	if (s != text) {
		text = s;
		update(r);
	}
}

void TextView::lua_setText(std::string s, void* rr) {
	SDL_Renderer* r = (SDL_Renderer*)rr;
	if (s != text) {
		text = s;
		update(r);
	}
}

std::string TextView::getText() {
	return text;
}

int TextView::getWidth()
{
	return tex.getW();
}

int TextView::getHeight()
{
	return tex.getH();
}
