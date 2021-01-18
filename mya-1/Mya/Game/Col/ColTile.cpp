#include "ColTile.h"

ColTile::ColTile(float _x, float _y, float _w, float _h, float _xo, float _yo, void* _updateCallback, Animation* _ani, bool isCollidable, void* onCollideCallback)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	xo = _xo;
	yo = _yo;
	updateCallback = _updateCallback;
	ani = _ani;
	which = true;
}

ColTile::ColTile(float _x, float _y, float _w, float _h, float _xo, float _yo, void* _updateCallback, Sprite* _spr, bool isCollidable, void* onCollideCallback)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	xo = _xo;
	yo = _yo;
	updateCallback = _updateCallback;
	spr = _spr;
	which = false;
}

std::string ColTile::getID()
{
	return id;
}

float ColTile::getX()
{
	return x;
}

float ColTile::getY()
{
	return y;
}

float ColTile::getW()
{
	return w;
}

float ColTile::getH()
{
	return h;
}

float ColTile::getXO()
{
	return xo;
}

float ColTile::getYO()
{
	return yo;
}

void* ColTile::getUpdateCallback()
{
	return updateCallback;
}

bool ColTile::getWhich()
{
	return which;
}

Animation* ColTile::getAnimation()
{
	return ani;
}

Sprite* ColTile::getSprite()
{
	return spr;
}

bool ColTile::getIsCollidable()
{
	return isCollidable;
}

void* ColTile::getOnCollideCallback()
{
	return onCollideCallback;
}

void ColTile::setX(float _x)
{
	x = _x;
}

void ColTile::setY(float _y)
{
	y = _y;
}

void ColTile::setW(float _w)
{
	w = _w;
}

void ColTile::setH(float _h)
{
	h = _h;
}

void ColTile::setXO(float _xo)
{
	xo = _xo;
}

void ColTile::setYO(float _yo)
{
	yo = _yo;
}

void ColTile::setUpdateCallback(void* _callback)
{
	updateCallback = _callback;
}

void ColTile::setWhich(bool _which)
{
	which = _which;
}

void ColTile::setAnimation(Animation* _animation)
{
	ani = _animation;
}

void ColTile::setSprite(Sprite* _sprite)
{
	spr = _sprite;
}

void ColTile::setIsCollidable(bool _isCollidable)
{
	isCollidable = _isCollidable;
}

void ColTile::setOnCollideCallback(void* _onCollideCallback)
{
	onCollideCallback = _onCollideCallback;
}
