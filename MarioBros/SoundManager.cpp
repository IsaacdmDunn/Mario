#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
	//deletes the music from memory
	Mix_FreeMusic(mMusic);
	mMusic = NULL;
	Mix_FreeChunk(mSound);
	mSound = NULL;
}

void SoundManager::LoadMusic(std::string filePath)
{
	//Loads the music into memory
	mMusic = Mix_LoadMUS(filePath.c_str());
	if (!mMusic) {
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void SoundManager::PlayMusic(int numOfLoops)
{
	//Plays the music
	Mix_PlayMusic(mMusic, numOfLoops);
}

void SoundManager::StopMusic()
{
	//Stops the music
	Mix_HaltMusic();
}

void SoundManager::PauseMusic()
{
	//Pauses music
	Mix_PauseMusic();
}

void SoundManager::ResumeMusic()
{
	//Resumes music
	Mix_ResumeMusic();
}

Mix_Chunk* SoundManager::LoadSoundEffect(std::string filePath)
{
	//Loads the sound
	mSound = Mix_LoadWAV(filePath.c_str());
	if (!mSound) { //if mSound is equal to null
		printf("Could not load %s\nMix Error: %s", filePath.c_str(), Mix_GetError()); //output error
	}
	//return mSound
	return mSound;
}

void SoundManager::PlaySoundEffect(Mix_Chunk* sound)
{
	//plays the sound that is passed and does not loop
	Mix_PlayChannel(-1, sound, 0);
}