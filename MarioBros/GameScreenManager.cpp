//libraries
#include "GameScreenManager.h"

//constructor
GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	ChangeScreen(startScreen);
}

//destructor
GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

//render current screen
void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

//update screen manager
void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	//update current screen
	mCurrentScreen->Update(deltaTime, e);

	//if screen is set to a new screen then change screen
	if (mCurrentScreen->GetScreenToChange() != SCREEN_NULL) 
	{
		ChangeScreen(mCurrentScreen->GetScreenToChange());
	}
	
}

//change screen
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
	//null screen
	case SCREEN_NULL:
		
		break;

	//intro/ main menu screen
	case SCREEN_INTRO:
		GameScreenIntro* intro;
		intro = new GameScreenIntro(mRenderer);
		mCurrentScreen = (GameScreen*)intro;
		intro = NULL;
		delete intro;
		std::cout << "intro  loading..." << std::endl;
		break;

	//level 1 screen
	case SCREEN_LEVEL1:
		GameScreenLevel* level1;
		level1 = new GameScreenLevel(mRenderer);
		mCurrentScreen = (GameScreen*)level1;
		level1 = NULL;
		delete level1;
		std::cout << "level 1 loading..." << std::endl;
		break;

	//level 2 screen
	case SCREEN_LEVEL2:
		GameScreenLevel2* level2;
		level2 = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)level2;
		level2 = NULL;
		delete level2;
		std::cout << "level 2 loading..." << std::endl;
		break;

	//game over screen
	case SCREEN_GAMEOVER:
		GameScreenGameOver* gameOver;
		gameOver = new GameScreenGameOver(mRenderer);
		mCurrentScreen = (GameScreen*)gameOver;
		gameOver = NULL;
		delete gameOver;
		std::cout << "level 2 loading..." << std::endl;
		break;
	}
}
