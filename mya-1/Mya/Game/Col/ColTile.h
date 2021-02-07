#pragma once

#include <String>

#include "../../Graphics/Animation.h"
#include "../../Graphics/Sprite.h"

class ColTile {
public:
	std::string id = "null", data="";
	float x = 0; // main x for the tile
	float y = 0; // main y for the tile
	float w = 0; // the width of the tile
	float h = 0; // the height of the tile
	float xo = 0; // the x offset for the tile
	float yo = 0; // the y offset for the tile
	void* updateCallback = NULL; // called every update tick
	bool isCollidable = false; // is the tile collidable
	void* onCollideCallback = NULL; // called when something collides with tile

	bool which = false; // use spr (false) or ani (true)
	Animation* ani = NULL; // animation alloc
	Sprite* spr = NULL; // sprite alloc

	ColTile(float x, float y, float w, float h, float xo, float yo, void* updateCallback, Animation* ani, bool isCollidable, void* onCollideCallback);
	ColTile(float x, float y, float w, float h, float xo, float yo, void* updateCallback, Sprite* spr, bool isCollidable, void* onCollideCallback);

	std::string getID();
	float getX();
	float getY();
	float getW();
	float getH();
	float getXO();
	float getYO();
	void* getUpdateCallback();
	bool getWhich();
	Animation* getAnimation();
	Sprite* getSprite();
	bool getIsCollidable();
	void* getOnCollideCallback();

	void setX(float _x);
	void setY(float _y);
	void setW(float _w);
	void setH(float _h);
	void setXO(float _xo);
	void setYO(float _yo);
	void setUpdateCallback(void* _callback);
	void setWhich(bool _which);
	void setAnimation(Animation* _animation);
	void setSprite(Sprite* _sprite);
	void setIsCollidable(bool _isCollidable);
	void setOnCollideCallback(void* _onCollideCallback);
};