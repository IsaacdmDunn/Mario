//libraries
#include "SoundManager.h"

//constructor
SoundManager::SoundManager()
{
}

//destructor
SoundManager::~SoundManager()
{
	//deletes the music from memory
	Mix_FreeMusic(mMusic);
	mMusic = NULL;
	Mix_FreeChunk(mSound);
	mSound = NULL;
}

//loads music
void SoundManager::LoadMusic(std::string filePath)
{
	mMusic = Mix_LoadMUS(filePath.c_str());
	if (!mMusic) {
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

//plays music
void SoundManager::PlayMusic(int numOfLoops)
{
	Mix_PlayMusic(mMusic, numOfLoops);
}

//stops music
void SoundManager::StopMusic()
{
	Mix_HaltMusic();
}

//pauses music
void SoundManager::PauseMusic()
{
	Mix_PauseMusic();
}

//resumes
void SoundManager::ResumeMusic()
{
	Mix_ResumeMusic();
}

//load sound effect
Mix_Chunk* SoundManager::LoadSoundEffect(std::string filePath)
{
	mSound = Mix_LoadWAV(filePath.c_str());
	if (!mSound) 
	{
		printf("Could not load %s\nMix Error: %s", filePath.c_str(), Mix_GetError()); //output error
	}
	return mSound;
}

//play sound effect
void SoundManager::PlaySoundEffect(Mix_Chunk* sound)
{
	Mix_PlayChannel(-1, sound, 0);
}