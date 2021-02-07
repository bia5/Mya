#include "ColChunk.h"

__Object::__Object()
{
}

ColChunk::ColChunk()
{
    
}

ColTile* ColChunk::getUndertile(int x, int y)
{
    return &undertiles[(y*chunkSize)+x];
}

void ColChunk::setUndertile(int x, int y, ColTile tile)
{
    undertiles[(y * chunkSize) + x] = tile;
}

ColTile* ColChunk::getTile(int x, int y)
{
    return &tiles[(y * chunkSize) + x];
}

void ColChunk::setTile(int x, int y, ColTile tile)
{
    tiles[(y * chunkSize) + x] = tile;
}

ColTile* ColChunk::getObject(int id)
{
    for (__Object obj : objects)
        if (obj.id == id)
            return obj.tile;
    return nullptr;
}

int ColChunk::setObject(ColTile tile)
{
    __Object obj;
    obj.tile = &tile;
    ids++;
    obj.id = ids;
    objects.push_back(obj);
    return ids;
}

ColEntity* ColChunk::getEntity(int id)
{
    for (__Object obj : objects)
        if (obj.id == id)
            return obj.entity;
    return nullptr;
}

int ColChunk::setEntity(ColEntity entity)
{
    __Object obj;
    obj.entity = &entity;
    ids++;
    obj.id = ids;
    objects.push_back(obj);
    return ids;
}

void ColChunk::generate(ColTile tile)
{
    for (int yy = 0; yy < chunkSize; yy++)
        for (int xx = 0; xx < chunkSize; xx++) {
            tile.x = (x*chunkSize)+xx;
            tile.y = (y*chunkSize)+yy;
            setUndertile(xx, yy, tile);//this should work :)
        }
}

void ColChunk::save(std::string wrld)
{
    //undertiles
    std::string _undertiles = "";
    for (int yy = 0; yy < chunkSize; yy++)
        for (int xx = 0; xx < chunkSize; xx++) {
            ColTile* t = getUndertile(xx, yy);
            std::string o = "nil";
            if (t) {
                std::string oo = "";
                if (t->isCollidable)
                    oo = "true";
                else
                    oo = "false";
                o = "{(" + std::to_string(t->x) + "_" + std::to_string(t->y) + ")," + t->id + "," + oo + ",(" + t->data + ")}";
            }
            if(o!="nil")
                _undertiles = _undertiles + o;
        }

    //tiles
    std::string _tiles = "";


    //objects
    std::string _objects = "";


    //entities
    std::string _entities = "";


    //WRITE IT
    std::string _output = _undertiles + "|" + _tiles + "|" + _objects + "|" + _entities;

}

void ColChunk::load(std::string wrld)
{
    //undertiles
    //tiles
    //objects
    //entities
}
