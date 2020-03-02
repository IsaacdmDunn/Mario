#include "GameScreenLevel.h"
#include <iostream>
#include "Texture2D.h"
#include "PowBlock.h"
#include "Collisions.h"

//constructer
GameScreenLevel::GameScreenLevel(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	mLevelMap = NULL;
}

//destructer - deletes all pointers in level
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

//level update
void GameScreenLevel::Update(float deltaTime, SDL_Event e)
{
	//POW block screen wobble
	if (mScreenShake) {
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;
		//if wobble timer ends stop screen shake
		if (mScreenShakeTime <= 0.0f) {
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	//update level objects
	Luigi->Update(deltaTime, e);
	Mario->Update(deltaTime, e);
	UpdatePowBlock();
}

//update POW block
void GameScreenLevel::UpdatePowBlock()
{
	//if mario jumps at POW block then activate
	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), Mario->GetCollisionBox()))
	{
		std::cout << "touch 2";
		if (mPowBlock->IsAvailable())
		{
			if (Mario->mJumping) 
			{
				mPowBlock->TakeAHit();

			}
		}
	}
}

//set screen to shake
void GameScreenLevel::ShakeScreen()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
}

//render level objects
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

	//set default values
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	//create level objects
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

//sets the level map
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
