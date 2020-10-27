#pragma once

#include <iostream>
#include <SDL_mixer.h>

class Music {
public:
	Music(std::string);

	void destroy();

	void play();
	void pause();
	void resume();
	bool isPaused();
	void stop();
	bool isPlaying();
	void setVolume(int);
	int getVolume();

private:
	Mix_Music* music = NULL;
};