//libraries
#include "GameScreenIntro.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "GameScreenManager.h"

//constructor
GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();

	//plays level music
	mMusicSystem = new SoundManager();
	mMusicSystem->LoadMusic("Audio/Mario.mp3");
	mMusicSystem->PlayMusic();
}

//destructor
GameScreenIntro :: ~GameScreenIntro()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete mIntroText;
	mIntroText = NULL;
}

//renders game screen
void GameScreenIntro::Render()
{
	mBackgroundTexture->Render(Vector2D(0.0, 0.0), SDL_FLIP_NONE);
	mIntroText->Render(Vector2D(0.0, 0.0), SDL_FLIP_NONE);
}

//updates game screen
void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
	//if space is pressed then go to level 1
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			mScreenToChange = SCREEN_LEVEL1;
			break;
		default:
			break;
		}
	}
}

//sets up the game screen
bool GameScreenIntro::SetUpLevel()
{
	//Load the background Texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadTextureFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture";
		return false;
	}

	//loads the "press space to play" text image
	mIntroText = new Texture2D(mRenderer);
	if (!mIntroText->LoadTextureFromFile("Images/IntroText.png"))
	{
		std::cout << "Failed to load background texture";
		return false;
	}
	return false;
}

