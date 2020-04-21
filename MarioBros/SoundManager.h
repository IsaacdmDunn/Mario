#pragma once

//libraries
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	Mix_Chunk* LoadSoundEffect(std::string filePath);
	void PlaySoundEffect(Mix_Chunk* sound);
	void LoadMusic(std::string filePath);
	void PlayMusic(int numOfLoops = -1);
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();
	bool IsPlaying() const { return Mix_PlayingMusic(); }

private:
	Mix_Chunk* mSound;
	Mix_Music* mMusic;
};