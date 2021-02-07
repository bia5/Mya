#pragma once

#include <vector>
#include <string>

//File poo poo
#include <fstream>

#include "ColEntity.h"
#include "ColTile.h"

struct __Object {
	__Object();

	ColTile* tile;
	ColEntity* entity;
	int id;
};

class ColChunk {
public:
	int chunkSize = 32;
	int ids = 1;
	int x = -1, y = -1;

	std::vector<ColTile> undertiles; //Something needs to appear under everything neatly...
	std::vector<ColTile> tiles; //tiles xd
	std::vector<__Object> objects; //Can be anything, walls, flowers, a fuckin rock.
	std::vector<__Object> entities; //A person, ant, a friggin car
	
	ColChunk();

	ColTile* getUndertile(int x, int y);
	void setUndertile(int x, int y, ColTile tile);

	ColTile* getTile(int x, int y);
	void setTile(int x, int y, ColTile tile);

	ColTile* getObject(int id);
	int setObject(ColTile tile);
	
	ColEntity* getEntity(int id);
	int setEntity(ColEntity entity);


	void generate(ColTile tile);

	//FILE DOO DOO
	void save(std::string wrld);
	void load(std::string wrld);
private:
};