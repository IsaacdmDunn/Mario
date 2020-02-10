#include "GameScreenLevel.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
//#include "Character.cpp"


GameScreenLevel::GameScreenLevel(SDL_Renderer* renderer) : GameScreen(renderer)
{
	/*mRenderer = renderer;*/
	SetUpLevel();
}

GameScreenLevel::~GameScreenLevel()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete Luigi;
	Luigi = NULL;
	
	delete Mario;
	Mario = NULL;
}

void GameScreenLevel::Update(float deltaTime, SDL_Event e)
{
	Luigi->Update(deltaTime, e);
	Mario->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(Mario, Luigi));
	if (Collisions::Instance()->Box(Mario->GetCollisionBox(), Luigi->GetCollisionBox()));
}

void GameScreenLevel::Render()
{
	//draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	Luigi->Render();
	Mario->Render();
}

bool GameScreenLevel::SetUpLevel()
{
	Luigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(64, 330));
	Mario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(128, 330));

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadTextureFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}
	return true;
}
