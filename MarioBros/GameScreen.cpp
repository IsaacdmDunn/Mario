#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	renderer = mRenderer;
}

GameScreen::~GameScreen()
{
	mRenderer = NULL;
}

void GameScreen::Render()
{
	
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{
}
