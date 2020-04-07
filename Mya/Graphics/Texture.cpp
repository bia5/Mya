#include "Texture.h"

#include "..//Mya.h"

Texture::Texture()
{
}

Texture::Texture(std::string path, SDL_Renderer* renderer) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		w = loadedSurface->w;
		h = loadedSurface->h;
		//std::cout << "Loaded texture: " << path.c_str() << "!\n";
		SDL_FreeSurface(loadedSurface);
	}
}

Texture::Texture(SDL_Surface* loadedSurface, SDL_Renderer* renderer) {
	if (loadedSurface == NULL) {
		//std::cout << "Cannot convert a NULL SDL_Surface into SDL_Texture... Why would you even try?" << std::endl;
	}
	else {
		if (a == true) {
			//I wrote this a year ago, and never commented how it worked
			//I just remember if I didnt do this, it caused a horrible
			//memory leak! iirc it was mostly with the TextView refreshing
			//every frame so it would re-init this class every frame.
			//So if it was init'd before it would destroy before replaceing
			//the SDL_Surface. 10/10 comment
			SDL_DestroyTexture(texture);
			//std::cout << "a";
		}

		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL) {
			std::cout << "Texture::Texture(SDL_Surface*, SDL_Renderer*) texture = NULL. It errored!" << std::endl;
		}
		w = loadedSurface->w;
		h = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		a = true;
	}
}

Texture::Texture(std::string path, Mya* rendererr) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		texture = SDL_CreateTextureFromSurface(rendererr->getRenderer(), loadedSurface);
		if (texture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		w = loadedSurface->w;
		h = loadedSurface->h;
		//std::cout << "Loaded texture: " << path.c_str() << "!\n";
		SDL_FreeSurface(loadedSurface);
	}
}

SDL_Texture* Texture::getTexture() {
	return texture;
}

void Texture::destroy() {
	SDL_DestroyTexture(texture);
}

int Texture::getW()
{
	return w;
}

int Texture::getH()
{
	return h;
}
