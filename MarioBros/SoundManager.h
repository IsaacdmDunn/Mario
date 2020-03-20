#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	//Loads a sound effect
	Mix_Chunk* LoadSoundEffect(std::string filePath);

	//Plays a sound effect
	void PlaySoundEffect(Mix_Chunk* sound);

	//Loads the music
	void LoadMusic(std::string filePath);

	//Plays the music
	void PlayMusic(int numOfLoops = -1);

	//Stops the music
	void StopMusic();

	//Pauses the music
	void PauseMusic();

	//Resumes the music
	void ResumeMusic();

	//returns true if the music is playing
	bool IsPlaying() const { return Mix_PlayingMusic(); }

private:
	Mix_Chunk* mSound;
	Mix_Music* mMusic;
};