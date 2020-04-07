#include "Sprite.h"

Sprite::Sprite(Texture* texture) {
	if (texture != NULL)
		canRRender = true;
	else
		canRRender = false;
	tex = texture;
}

void Sprite::setTexture(Texture* texture) {
	if (texture != NULL)
		canRRender = true;
	else
		canRRender = false;
	tex = texture;
}

void Sprite::destroy() {
	tex->destroy();
}

void Sprite::update() {}

void Sprite::render(SDL_Renderer* renderer) {
	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = tex->w;
	a.h = tex->h;
	w = a.w;
	h = a.h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);
		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Sprite::render(SDL_Renderer* renderer, int w, int h) {
	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = w;
	a.h = h;
	this->w = w;
	this->h = h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);
		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Sprite::render(SDL_Renderer* renderer, int w, int h, bool f) {
	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = w;
	a.h = h;
	this->w = w;
	this->h = h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender) {
		if (f)
			SDL_RenderCopyEx(renderer, tex->getTexture(), NULL, &a, 0.0, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);

		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Sprite::renderWithBounds(SDL_Renderer* renderer) {
	w = bounds.w;
	h = bounds.h;
	if (canRRender) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &bounds);

		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Sprite::setBounds(SDL_Rect b) {
	bounds = b;
}

SDL_Rect Sprite::getBounds() {
	return bounds;
}

void Sprite::setAutoBounds(bool b) {
	autoSetBounds = b;
}

void Sprite::setX(float _x)
{
	x = _x;
}

void Sprite::setY(float _y)
{
	y = _y;
}

int Sprite::getX()
{
	return x;
}

int Sprite::getY()
{
	return y;
}

void Sprite::setRenderOutline(bool yeet)
{
	renderBounds = yeet;
}

void Sprite::setOutlineColor(int a, int b, int c, int d)
{
	outlineColor1 = a;
	outlineColor2 = b;
	outlineColor3 = c;
	outlineColor4 = d;
}

void Sprite::lua_render(void* rrenderer, int w, int h) {
	SDL_Renderer* renderer = (SDL_Renderer*)rrenderer;

	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = w;
	a.h = h;
	this->w = w;
	this->h = h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);
		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, outlineColor1, outlineColor2, outlineColor3, outlineColor4);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Sprite::lua_renderFlip(void* rrenderer, int w, int h, bool f) {
	SDL_Renderer* renderer = (SDL_Renderer*)rrenderer;

	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = w;
	a.h = h;
	this->w = w;
	this->h = h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender) {
		if (f)
			SDL_RenderCopyEx(renderer, tex->getTexture(), NULL, &a, 0.0, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);

		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, outlineColor1, outlineColor2, outlineColor3, outlineColor4);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Sprite::lua_renderDefault(void* rrenderer) {
	SDL_Renderer* renderer = (SDL_Renderer*)rrenderer;

	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = tex->w;
	a.h = tex->h;
	w = a.w;
	h = a.h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);
		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

bool Sprite::isColliding(Sprite spr) {
	if (isPointInRect(x, y, spr.x, spr.y, spr.w, spr.h) ||
		isPointInRect(x + w, y, spr.x, spr.y, spr.w, spr.h) ||
		isPointInRect(x, y + h, spr.x, spr.y, spr.w, spr.h) ||
		isPointInRect(x + w, y + h, spr.x, spr.y, spr.w, spr.h)) {
		return true;
	}

	return false;
}

bool Sprite::isPointColliding(int x, int y) {
	if (x > this->x && x < (this->x + w)) {
		if (y > this->y && y < (this->y + h)) {
			return true;
		}
	}

	return false;
}

bool Sprite::isPointInRect(float x, float y, float rx, float ry, float rw, float rh) {
	if (x > rx && x < (rx + rw)) {
		if (y > ry && y < (ry + rh)) {
			return true;
		}
	}

	return false;
}
