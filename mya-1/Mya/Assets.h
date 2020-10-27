#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Graphics/Texture.h"
class Mya;

class Object {
public:
	std::string id = "null";
	void* obj;
};

class Assets {
public:
	Mya* mya;
	std::vector<Object*> textures;

	Assets(Mya*);

	bool loadTexture(std::string id, std::string pathAccordingToExec);
	Texture* getTexture(std::string);

	int getTotalAssets();
};