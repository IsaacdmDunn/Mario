//library
#include "GameScreen.h"

//constructor
GameScreen::GameScreen(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

//destructor
GameScreen::~GameScreen()
{
	mRenderer = NULL;
}

//renders game screen
void GameScreen::Render()
{
}

//updates game screen
void GameScreen::Update(float deltaTime, SDL_Event e)
{
}
