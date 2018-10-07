#ifndef sound_h
#define sound_h

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Sound
{
private : 
	Mix_Music* backgroundMusic;
public : 
	Sound(std::string filename);
	~Sound();
	void PlayMusic(int volume);
};

#endif