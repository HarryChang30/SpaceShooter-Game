#include "sound.h"

Sound::Sound(std::string filename)
{
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

	backgroundMusic = Mix_LoadMUS(filename.c_str());
}

void Sound::PlayMusic(int volume)
{
	if(Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(backgroundMusic,-1);
		Mix_VolumeMusic(volume);
	}
}

Sound::~Sound()
{	
	Mix_FreeMusic(backgroundMusic);
	Mix_Quit();
}