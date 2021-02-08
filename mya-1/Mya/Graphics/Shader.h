#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL.h>
#include <glad/glad.h>

class Shader {
public:
	unsigned int ID; //Shader's program ID

	Shader(std::string vertexPath, std::string fragmentPath);

	void use();

	void setBool(std::string name, bool value);
	void setInt(std::string name, int value);
	void setFloat(std::string name, float value);

	void destroy();
};