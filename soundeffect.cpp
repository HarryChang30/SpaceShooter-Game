#include "soundeffect.h"

SoundEffect::SoundEffect(std::string filename)
{

	attackSound = Mix_LoadWAV(filename.c_str());

}

void SoundEffect::PlaySoundEffect(int volume)
{
	Mix_PlayChannel(-1,attackSound,0);
	Mix_VolumeChunk(attackSound,volume);
}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(attackSound);
}