#pragma once

#include <vector>
#include <string>

#include "ColChunk.h"

class ColWorld {
public:
	int width = 256, height = 256; // In chunks
	std::vector<ColChunk> chunkies; //all dah chunks

	ColWorld();

	void generateChunks();
private:
};