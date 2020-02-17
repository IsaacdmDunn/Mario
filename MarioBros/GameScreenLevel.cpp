#include "GameScreenLevel.h"
#include <iostream>
#include "Texture2D.h"

GameScreenLevel::GameScreenLevel(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	mLevelMap = NULL;

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

	SetLevelMap();

	Luigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(64, 0), mLevelMap);
	Mario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(128, 0), mLevelMap);

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadTextureFromFile("Images/backgroundMB.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}
}

void GameScreenLevel::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear up old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//set the new map
	mLevelMap = new LevelMap(map);
}
