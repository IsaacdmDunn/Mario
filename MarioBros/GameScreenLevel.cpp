#include "GameScreenLevel.h"
#include <iostream>
#include "Texture2D.h"

GameScreenLevel::GameScreenLevel(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	SetUpLevel();
}

GameScreenLevel::~GameScreenLevel()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete Luigi;
	Luigi = NULL;
}

void GameScreenLevel::Update(float deltaTime, SDL_Event e)
{
	Luigi->Update(deltaTime, e);
}

void GameScreenLevel::Render()
{
	//draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	Luigi->Render();
}

bool GameScreenLevel::SetUpLevel()
{
	Luigi = new Character(mRenderer, "Images/Luigi.png", Vector2D(64, 330));

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadTextureFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}
}
