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

	ColEntity(std::string _id, Animation* _ani, float _x, float _y, float _xoff, float _yoff, void* _updateCallback, float _mvSpeed);
	ColEntity(std::string _id, Sprite* _spr, float _x, float _y, float _xoff, float _yoff, void* _updateCallback, float _mvSpeed);

	std::string getID();
	float getX();
	float getY();
	float getW();
	float getH();
	float getXO();
	float getYO();
	float getMovementSpeed();

	bool getUp();
	bool getDn();
	bool getRt();
	bool getLt();

	void* getUpdateCallback();
	bool getIsCollidable();
	void* getOnCollideCallback();

	bool getWhich();
	Animation* getAnimation();
	Sprite* getSprite();
	
	void setID(std::string _id);
	void setX(float _x);
	void setY(float _y);
	void setW(float _w);
	void setH(float _h);
	void setXO(float _xo);
	void setYO(float _yo);
	void setMovementSpeed(float _movementSpeed);

	void setUp(bool _up);
	void setDn(bool _dn);
	void setRt(bool _rt);
	void setLt(bool _lt);

	void setUpdateCallback(void* _updateCallback);
	void setIsCollidable(bool _isCollidable);
	void setOnCollideCallback(void* _onCollideCallback);

	void setWhich(bool _which);
	void setAnimation(Animation* _ani);
	void setSprite(Sprite* _spr);
private:
};