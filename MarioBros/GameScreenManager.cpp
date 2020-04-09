#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel.h"
#include "GameScreenLevel2.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{

	mCurrentScreen->Update(deltaTime, e);

	if (mCurrentScreen->GetScreenToChange() != SCREEN_INTRO) 
	{
		ChangeScreen(mCurrentScreen->GetScreenToChange());
	}
	
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}
	
	//change the screen 
	switch (newScreen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		break;
	case SCREEN_LEVEL1:
		GameScreenLevel* level1;
		level1 = new GameScreenLevel(mRenderer);
		mCurrentScreen = (GameScreen*)level1;
		level1 = NULL;
		delete level1;
		std::cout << "level 1 loading..." << std::endl;
		break;
	case SCREEN_LEVEL2:
		GameScreenLevel2* level2;
		level2 = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)level2;
		level2 = NULL;
		delete level2;
		std::cout << "level 2 loading..." << std::endl;
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}
