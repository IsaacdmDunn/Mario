#include "GameScreenLevel.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"


GameScreenLevel::GameScreenLevel(SDL_Renderer* renderer) : GameScreen(renderer) {
	
	coinIndexToDelete = -1;
	enemyIndexToDelete = -1;
	SetUpLevel();
}

GameScreenLevel :: ~GameScreenLevel()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete Mario;
	Mario = NULL;
	delete Luigi;
	Luigi = NULL;

	delete mScoreSystem;
	mScoreSystem = NULL;

	delete mPowBlock;
	mPowBlock = NULL;
	mLevelMap = NULL;
	
	mEnemies.clear();
}

void GameScreenLevel::Render()
{
	mBackgroundTexture->Render(Vector2D(0.0, mBackgroundYPos), SDL_FLIP_NONE);
	mPowBlock->Render();

	Mario->Render();
	Luigi->Render();
	//std::cout << mEnemies[0]->GetPosition().y << std::endl;

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}
	
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}
}

void GameScreenLevel::Update(float deltaTime, SDL_Event e)
{
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);

	if (mScreenShake)
	{
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;
		if (mScreenShakeTime <= 0.0f)
		{
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	if (mEnemyRespawnTime < 0.0f)
	{
		mEnemyRespawnTime = KOOPA_RESPAWN_RATE;
		CreateKoopa(Vector2D(325, 320), FACING_LEFT, KOOPA_SPEED);
	}
	
}

void GameScreenLevel::UpdatePOWBlock()
{

	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), Mario->GetCollisionBox()) /*&& mPowBlock->IsAvailable*/)
	{
		if (Mario->mJumping == true)
		{
			ShakeScreen();
			mPowBlock->TakeAHit();
			Mario->CancelJump();
			mScoreSystem->mScore += 100;
			std::cout << "Score: " << mScoreSystem->mScore << std::endl;
		}
	}
	else if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), Luigi->GetCollisionBox()) /*&& mPowBlock->IsAvailable*/)
	{
		if (Luigi->mJumping == true)
		{
			ShakeScreen();
			mPowBlock->TakeAHit();
			Luigi->CancelJump();
			mScoreSystem->mScore += 100;
			std::cout << "Score: " << mScoreSystem->mScore << std::endl;
		}
	}

}

void GameScreenLevel::ShakeScreen()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
		//if the enemy is no longer alive then delete
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
			enemyIndexToDelete = -1;
		}

		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//check if enemy of on the bottom row of the level map
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				//check if enemy is offscreen
				if (mEnemies[i]->GetPosition().x < (float)(mEnemies[i]->GetCollisionBox().width * 0.5f) ||
					mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
				{
				}
			}

			//update enemies
			mEnemies[i]->Update(deltaTime, e);

			//check if enemy is off screen
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) &&
				(mEnemies[i]->GetPosition().x > 64.0f  || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//koopa dies
				mEnemies[i]->SetAlive(false);
			}
			else
			{
				//check if enemies collides with player
				if (Collisions::Instance()->Circle(mEnemies[i], Mario))
				{
					std::cout << Collisions::Instance()->Circle(mEnemies[i], Mario) << std::endl;
					//Mario.SetState(CHARACTER_PLAYER_DEATH);
					if (mEnemies[i]->GetAlive() == true)
					{
						//player dies
					}
					else
					{
						//koopa dies
						mEnemies[i]->SetAlive(false);
					}
				}
			}

			
		}
	}
}

void GameScreenLevel::UpdateCoins(float deltaTime, SDL_Event e)
{
	
	if (!mCoins.empty())
	{
		if (coinIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
			coinIndexToDelete = -1;
		}
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			if (Collisions::Instance()->Box(mCoins[i]->GetCollisionBox(), Mario->GetCollisionBox()) /*&& mPowBlock->IsAvailable*/)
			{
					mScoreSystem->mScore += 100;
					coinIndexToDelete = i;
			}
			
			//update coins
			mCoins[i]->Update(deltaTime, e);

			//check if coin if coin is out of bounds and delete it
			if ((mCoins[i]->GetPosition().y > 300.0f || mCoins[i]->GetPosition().y <= 64.0f) &&
				(mCoins[i]->GetPosition().x > 64.0f || mCoins[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				coinIndexToDelete = i;
			}
		}

			
	}
	
}

void GameScreenLevel::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	mCharacterKoopa = new CharacterKoopa(mRenderer, "Images/Koopa.png" , position, mLevelMap, direction, speed);
	mEnemies.push_back(mCharacterKoopa);
}

void GameScreenLevel::CreateCoins(Vector2D position)
{
	mCharacterCoin = new CharacterCoin(mRenderer, "Images/Coin.png", position, mLevelMap, 0);
	mCoins.push_back(mCharacterCoin);
}

bool GameScreenLevel::SetUpLevel()
{
	//set screen shake system to default
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	//setup the player character
	SetLevelMap();
	Mario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	Luigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(128, 330), mLevelMap);

	mScoreSystem = new ScoreSystem();

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	CreateCoins(Vector2D(325, 32));
	CreateCoins(Vector2D(292, 32));
	CreateCoins(Vector2D(260, 32));

	//Set up POW block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);


	//Load the background Texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadTextureFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture";
		return false;
	}
	return false;
}

void GameScreenLevel::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	//Clear up any old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;

	}

	//Set up the new one
	mLevelMap = new LevelMap(map);


}
