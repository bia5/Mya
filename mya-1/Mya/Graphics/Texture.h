#pragma once

#include <string>
#include <iostream>

#include <SDL.h>
#include <glad/glad.h>

class Texture {
public:
	unsigned int texture;
	int width = -1, height = -1, nrChannels = -1;

	Texture(std::string path);

	void use();
	void destroy();
};