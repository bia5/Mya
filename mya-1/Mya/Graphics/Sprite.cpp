#include "Sprite.h"

Sprite::Sprite(float _x, float _y, float _w, float _h, Shader* s, Texture* t) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	updateVertices();
	shader = s;
	texture = t;
}

void Sprite::render()
{
	shader->use();
	texture->use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::destroy() {

}

void Sprite::setXY(float _x, float _y) {
	x = _x;
	y = _y;
	updateVertices();
}

float Sprite::getX() {
	return x;
}

float Sprite::getY() {
	return y;
}

void Sprite::updateVertices() {
	vertices[24] = x;
	vertices[25] = y;

	vertices[0] = x + w;
	vertices[1] = y;

	vertices[16] = x;
	vertices[17] = y + h;

	vertices[8] = x + w;
	vertices[9] = y + h;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
