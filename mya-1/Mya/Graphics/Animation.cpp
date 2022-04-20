#include "Animation.h"

#pragma warning( disable : 4244 ) 

Animation::Animation(std::string texid, int framess, int fpss, Assets* ass) : Sprite(NULL){
	assets = ass;
	fps = fpss;
	texID = texid;
	frames = framess;
	for (int i = 0; i < frames; i++) { // For debug purposes :)
		if (assets->getTexture(texID+std::to_string(i)) == NULL)
			std::cout << "ERROR: Asset Missing: "+ texID + std::to_string(i) +"\n";
	}

	timepertick = 1000 / fps;
	tex = assets->getTexture(texID + std::to_string(frame));
	timer = std::clock();
	canRRender = true;
}

void Animation::setFrame(int f)
{
	frame = f;
}

void Animation::setTexID(std::string id)
{
	texID = id;
}

void Animation::setFPS(int f)
{
	fps = f;
	timepertick = 1000 / fps;
}

void Animation::setLooped(bool p)
{
	loop = p;
}

bool Animation::isFinished()
{
	return finished;
}

void Animation::reset()
{
	frame = 0;
	finished = false;
}

void Animation::render(SDL_Renderer* renderer) {
	overall += (std::clock() - timer);
	while (overall >= timepertick) {
		overall -= timepertick;
		frame++;
		if (frame > frames)
			if(loop)
				frame = 0;
			else
				finished = true;
		if (!finished)
			tex = assets->getTexture(texID + std::to_string(frame));
	}
	timer = std::clock();

	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = tex->w;
	a.h = tex->h;
	w = a.w;
	h = a.h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender && !finished) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);
		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Animation::render(SDL_Renderer* renderer, int w, int h) {
	overall += (std::clock() - timer);
	while (overall >= timepertick) {
		overall -= timepertick;
		frame++;
		if (frame > frames)
			if (loop)
				frame = 0;
			else
				finished = true;
		if (!finished)
			tex = assets->getTexture(texID + std::to_string(frame));
	}
	timer = std::clock();

	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = w;
	a.h = h;
	this->w = w;
	this->h = h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender && !finished) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);
		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Animation::render(SDL_Renderer* renderer, int w, int h, double angle, bool f) {
	overall += (std::clock() - timer);
	while (overall >= timepertick) {
		overall -= timepertick;
		frame++;
		if (frame > frames)
			if (loop)
				frame = 0;
			else
				finished = true;
		if (!finished)
			tex = assets->getTexture(texID + std::to_string(frame));
	}
	timer = std::clock();

	SDL_Rect a;
	a.x = x;
	a.y = y;
	a.w = w;
	a.h = h;
	this->w = w;
	this->h = h;

	if (autoSetBounds)
		bounds = a;

	if (canRRender && !finished) {
		if (f)
			SDL_RenderCopyEx(renderer, tex->getTexture(), NULL, &a, angle, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopyEx(renderer, tex->getTexture(), NULL, &a, angle, NULL, SDL_FLIP_NONE);

		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Animation::renderWithBounds(SDL_Renderer* renderer) {
	overall += (std::clock() - timer);
	while (overall >= timepertick) {
		overall -= timepertick;
		frame++;
		if (frame > frames)
			if (loop)
				frame = 0;
			else
				finished = true;
		if (!finished)
			tex = assets->getTexture(texID + std::to_string(frame));
	}
	timer = std::clock();

	w = bounds.w;
	h = bounds.h;
	if (canRRender && !finished) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &bounds);

		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Animation::lua_render(void* rrenderer, int w, int h) {
	overall += (std::clock() - timer);
	while (overall >= timepertick) {
		overall -= timepertick;
		frame++;
		if (frame > frames)
			if (loop)
				frame = 0;
			else
				finished = true;
		if (!finished)
			tex = assets->getTexture(texID + std::to_string(frame));
	}
	timer = std::clock();

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

	if (canRRender && !finished) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);
		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, outlineColor1, outlineColor2, outlineColor3, outlineColor4);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Animation::lua_renderFlip(void* rrenderer, int w, int h, double angle, bool f) {
	overall += (std::clock() - timer);
	while (overall >= timepertick) {
		overall -= timepertick;
		frame++;
		if (frame > frames)
			if (loop)
				frame = 0;
			else
				finished = true;
		if (!finished)
			tex = assets->getTexture(texID + std::to_string(frame));
	}
	timer = std::clock();

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

	if (canRRender && !finished) {
		if (f)
			SDL_RenderCopyEx(renderer, tex->getTexture(), NULL, &a, angle, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopyEx(renderer, tex->getTexture(), NULL, &a, angle, NULL, SDL_FLIP_NONE);

		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, outlineColor1, outlineColor2, outlineColor3, outlineColor4);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}

void Animation::lua_renderDefault(void* rrenderer) {
	overall += (std::clock() - timer);
	while (overall >= timepertick) {
		overall -= timepertick;
		frame++;
		if (frame > frames)
			if (loop)
				frame = 0;
			else
				finished = true;
		if (!finished)
			tex = assets->getTexture(texID + std::to_string(frame));
	}
	timer = std::clock();

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

	if (canRRender && !finished) {
		SDL_RenderCopy(renderer, tex->getTexture(), NULL, &a);
		if (renderBounds) {
			SDL_SetRenderDrawColor(renderer, 0, 69, 0, 0);
			SDL_RenderFillRect(renderer, &bounds);
			SDL_SetRenderDrawColor(renderer, 0, 0, 69, 0);
		}
	}
}
