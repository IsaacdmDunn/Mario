#include "GameScreenLevel.h"
#include <iostream>
#include "Texture2D.h"
#include "PowBlock.h"
#include "Collisions.h"

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
	delete mPowBlock;
	mPowBlock = NULL;
}

void GameScreenLevel::Update(float deltaTime, SDL_Event e)
{
	if (mScreenShake) {
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		if (mScreenShakeTime <= 0.0f) {
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	Luigi->Update(deltaTime, e);
	Mario->Update(deltaTime, e);
	UpdatePowBlock();
}

void GameScreenLevel::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), Mario->GetCollisionBox()))
	{
		std::cout << "touch";
		if (mPowBlock->IsAvailable())
		{
			if (Mario->mJumping) 
			{
				mPowBlock->TakeAHit();

			}
		}
	}
}

void GameScreenLevel::ShakeScreen()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
}

void GameScreenLevel::Render()
{
	//draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	Luigi->Render();
	Mario->Render();
	mPowBlock->Render();
}

bool GameScreenLevel::SetUpLevel()
{

	SetLevelMap();

	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	mPowBlock = new PowBlock(mRenderer, mLevelMap);
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
										{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
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
