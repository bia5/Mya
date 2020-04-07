#include "Assets.h"

#include "../Mya.h"

Assets::Assets(Mya* _mya) {
	mya = _mya;
	std::string p = SDL_GetBasePath();

	font = new Font(p + "assets/font.ttf");
}

void Assets::loadTexture(std::string id, std::string pathAccordingToExec) {
	std::string p = SDL_GetBasePath();
	Object ob;
	ob.id = id;
	Texture* t = new Texture(p + pathAccordingToExec, mya->getRenderer());
	ob.obj = (void*) t;
	textures.push_back(ob);
}

Texture* Assets::getTexture(std::string id) {
	for (int i = 0; i < textures.size(); i++) {
		if (textures[i].id == id) {
			return (Texture*)textures[i].obj;
		}
	}
}

Font Assets::getFont() {
	return *font;
}

int Assets::getTotalAssets()
{
	return textures.size();
}
