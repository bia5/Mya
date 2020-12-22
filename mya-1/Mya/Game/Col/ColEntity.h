#pragma once

#include <String>

#include "../../Graphics/Animation.h"
#include "../../Graphics/Sprite.h"

class ColEntity {
public:
	std::string id = "null";
	float x = 0; // main x for the tile
	float y = 0; // main y for the tile
	float w = 0; // the width of the tile
	float h = 0; // the height of the tile
	float xo = 0; // the x offset for the tile
	float yo = 0; // the y offset for the tile
	float movementSpeed = 0.03f; // movement speed

	bool up = false;
	bool dn = false;
	bool rt = false;
	bool lt = false;

	void* updateCallback = NULL; // called every update tick
	bool isCollidable = false; // is the tile collidable
	void* onCollideCallback = NULL; // called when something collides with tile

	bool which = false; // use spr (false) or ani (true)
	Animation* ani = NULL; // animation alloc
	Sprite* spr = NULL; // sprite alloc
private:
};