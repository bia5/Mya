#include "Assets.h"

#include "Mya.h"

Assets::Assets(Mya* _mya) {
	mya = _mya;
	std::string p = SDL_GetBasePath();
}

bool Assets::loadTexture(std::string id, std::string pathAccordingToExec) {
	for (int i = 0; i < textures.size(); i++) {
		if (textures[i]->id == id) {
			Texture* t = (Texture*)textures[i]->obj;
			t->destroy();
			textures[i] = NULL;
		}
	}
	std::string p = SDL_GetBasePath();
	Object* ob = new Object();
	ob->id = id;
	Texture* t = new Texture(p + pathAccordingToExec, mya->getRenderer());
	if (t != NULL) {
		ob->obj = (void*)t;
		textures.push_back(ob);
		return true;
	}
	else
		return false;
}

Texture* Assets::getTexture(std::string id) {
	for (int i = 0; i < textures.size(); i++) {
		if (textures[i] != NULL) {
			if (textures[i]->id == id) {
				return (Texture*)textures[i]->obj;
			}
		}
	}
	return NULL;
}

int Assets::getTotalAssets()
{
	return textures.size();
}
