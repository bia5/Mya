#include "Music.h"

Music::Music(std::string path){
	music = Mix_LoadMUS(path.c_str());
	if(music)
		std::cout << "Loaded music: " << path.c_str() << "!" << std::endl;
	else
		std::cout << "Error Loading music: " << path.c_str() << ", with error: " << Mix_GetError() << "!" << std::endl;
}

void Music::destroy() {
	Mix_FreeMusic(music);
	music = NULL;
}

void Music::play() {
	Mix_PlayMusic(music, 0);
}

void Music::pause() {
	Mix_PauseMusic();
}

void Music::resume() {
	Mix_ResumeMusic();
}

bool Music::isPaused()
{
	return Mix_PausedMusic();
}

void Music::stop() {
	Mix_HaltMusic();
}

bool Music::isPlaying()
{
	return Mix_PlayingMusic();
}

void Music::setVolume(int i)
{
	Mix_VolumeMusic(i);
}

int Music::getVolume()
{
	return Mix_VolumeMusic(-1);
}
