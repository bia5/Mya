#include "ColEntity.h"

ColEntity::ColEntity(std::string _id, Animation* _ani, float _x, float _y, float _xoff, float _yoff, void* _updateCallback, float _mvSpeed)
{
    id = _id;
    ani = _ani;
    which = true;
    x = _x;
    y = _y;
    xo = _xoff;
    yo = _yoff;
    updateCallback = _updateCallback;
    movementSpeed = _mvSpeed;
}

ColEntity::ColEntity(std::string _id, Sprite* _spr, float _x, float _y, float _xoff, float _yoff, void* _updateCallback, float _mvSpeed)
{
    id = _id;
    spr = _spr;
    which = false;
    x = _x;
    y = _y;
    xo = _xoff;
    yo = _yoff;
    updateCallback = _updateCallback;
    movementSpeed = _mvSpeed;
}

std::string ColEntity::getID()
{
    return id;
}

float ColEntity::getX()
{
    return x;
}

float ColEntity::getY()
{
    return y;
}

float ColEntity::getW()
{
    return w;
}

float ColEntity::getH()
{
    return h;
}

float ColEntity::getXO()
{
    return xo;
}

float ColEntity::getYO()
{
    return yo;
}

float ColEntity::getMovementSpeed()
{
    return movementSpeed;
}

bool ColEntity::getUp()
{
    return up;
}

bool ColEntity::getDn()
{
    return dn;
}

bool ColEntity::getRt()
{
    return rt;
}

bool ColEntity::getLt()
{
    return lt;
}

void* ColEntity::getUpdateCallback()
{
    return updateCallback;
}

bool ColEntity::getIsCollidable()
{
    return isCollidable;
}

void* ColEntity::getOnCollideCallback()
{
    return onCollideCallback;
}

bool ColEntity::getWhich()
{
    return which;
}

Animation* ColEntity::getAnimation()
{
    return ani;
}

Sprite* ColEntity::getSprite()
{
    return spr;
}

void ColEntity::setID(std::string _id)
{
    id = _id;
}

void ColEntity::setX(float _x)
{
    x = _x;
}

void ColEntity::setY(float _y)
{
    y = _y;
}

void ColEntity::setW(float _w)
{
    w = _w;
}

void ColEntity::setH(float _h)
{
    h = _h;
}

void ColEntity::setXO(float _xo)
{
    xo = _xo;
}

void ColEntity::setYO(float _yo)
{
    yo = _yo;
}

void ColEntity::setMovementSpeed(float _movementSpeed)
{
    movementSpeed = _movementSpeed;
}

void ColEntity::setUp(bool _up)
{
    up = _up;
}

void ColEntity::setDn(bool _dn)
{
    dn = _dn;
}

void ColEntity::setRt(bool _rt)
{
    rt = _rt;
}

void ColEntity::setLt(bool _lt)
{
    lt = _lt;
}

void ColEntity::setUpdateCallback(void* _updateCallback)
{
    updateCallback = _updateCallback;
}

void ColEntity::setIsCollidable(bool _isCollidable)
{
    isCollidable = _isCollidable;
}

void ColEntity::setOnCollideCallback(void* _onCollideCallback)
{
    onCollideCallback = _onCollideCallback;
}

void ColEntity::setWhich(bool _which)
{
    which = _which;
}

void ColEntity::setAnimation(Animation* _ani)
{
    ani = _ani;
}

void ColEntity::setSprite(Sprite* _spr)
{
    spr = _spr;
}
