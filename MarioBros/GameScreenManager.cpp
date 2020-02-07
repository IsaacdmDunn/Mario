#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{

	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}
	
	GameScreenLevel* tempScreen;

	switch (newScreen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_LEVEL2:
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}
