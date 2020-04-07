#pragma once

#include <iostream>
#include <SDL_mixer.h>

class Sound {
public:
	Sound(std::string);		//Object: Grabs and init' the sound file.

	void destroy();			//destroy: cleans up any messes.
	void play();			//play: plays the sound
	void setVolume(int);
	int getVolume();

private:
	Mix_Chunk* sound;
};