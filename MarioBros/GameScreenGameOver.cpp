//library
#include "GameScreenGameOver.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "GameScreenManager.h"

//constructor
GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();

	//plays game over sound
	mMusicSystem = new SoundManager();
	Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/GameOver.wav");
	mMusicSystem->PlaySoundEffect(mSound);
}

//destructor
GameScreenGameOver::~GameScreenGameOver()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete mIntroText;
	mIntroText = NULL;
}

//renders screen
void GameScreenGameOver::Render()
{
	mBackgroundTexture->Render(Vector2D(0.0, 0.0), SDL_FLIP_NONE);
	mIntroText->Render(Vector2D(0.0, 300.0), SDL_FLIP_NONE);
	mGameOverText->Render(Vector2D(0.0, 0.0), SDL_FLIP_NONE);
}

//updates screen
void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{
	//resets game when space is pressed
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
bool GameScreenGameOver::SetUpLevel()
{
	//Load the background Texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadTextureFromFile("Images/BackgroundMB2.png"))
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

	//loads the "game over" text image
	mGameOverText = new Texture2D(mRenderer);
	if (!mGameOverText->LoadTextureFromFile("Images/GameOverText.png"))
	{
		std::cout << "Failed to load background texture";
		return false;
	}
	return false;
}

