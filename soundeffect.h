#ifndef soundeffect_h
#define soundeffect_h

#include <SDL_mixer.h>
#include <SDL.h>
#include <string>

class SoundEffect
{
private : 
	Mix_Chunk* attackSound;

public : 
	SoundEffect(std::string filename);
	~SoundEffect();
	void PlaySoundEffect(int volume);
};

#endif