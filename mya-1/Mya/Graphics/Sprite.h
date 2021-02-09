#pragma once

#include <iostream>

#include <glad/glad.h>

#include "Shader.h"
#include "Texture.h"

class Sprite {
public:
	Shader* shader;
	Texture* texture;
	unsigned int VBO, VAO, EBO;

	float vertices[32] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	Sprite(float _x, float _y, float _w, float _h, Shader* s, Texture* t);

	void render();
	void destroy();

	void setX(float _x);
	void setY(float _y);
	void setW(float _w);
	void setH(float _h);
	float getX();
	float getY();
	float getW();
	float getH();

	bool isColliding(Sprite spr);
	bool isPointColliding(float xx, float yy);
	bool isPointInRect(float xx, float yy, float rx, float ry, float rw, float rh);
private:
	float x = 0.f, y = 0.f, w = 0.f, h = 0.f;
	void updateVertices();
};