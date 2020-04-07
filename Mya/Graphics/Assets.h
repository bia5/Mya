#pragma once

#include <iostream>
#include <vector>

#include "Font.h"
#include "Texture.h"
class Mya;

class Object {
public:
	std::string id = "null";
	void* obj;
};

class Assets {
public:
	Mya* mya;
	std::vector<Object> textures;
	Font* font;

	Assets(Mya*);

	void loadTexture(std::string id, std::string pathAccordingToExec);
	Texture* getTexture(std::string);
	Font getFont();
	int getTotalAssets();
};