#include "GameScreenLevel.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"


GameScreenLevel::GameScreenLevel(SDL_Renderer* renderer) : GameScreen(renderer) {
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
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
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
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//check if enemy of on the bottom row of the level map
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				//check if enemy is offscreen
				if (mEnemies[i]->GetPosition().x < (float)(mEnemies[i]->GetCollisionBox().width * 0.5f) ||
					mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
				{
					//mEnemies[i].SetAlive(false);
				}
			}

			//update enemies
			mEnemies[i]->Update(deltaTime, e);

			//check if enemies collides with player
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) &&
				(mEnemies[i]->GetPosition().x > 64.0f  || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
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
			else
			{
				if (Collisions::Instance()->Circle(mEnemies[i], Mario))
				{
					//Mario.SetState(CHARACTER_PLAYER_DEATH);
				}
			}

			//if the enemy is no longer alive then delete
			/*if (!mEnemies[i].GetAlive())
			{
				enemyIndexToDelete = i;
			}*/
		}

		//remove dead enemies
		if (enemyIndexToDelete != -1)
		{
			CreateCoins(mEnemies[enemyIndexToDelete]->GetPosition());
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!mCoins.empty())
	{
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			//check if coins of on the bottom row of the level map
			if (mCoins[i]->GetPosition().y > 300.0f)
			{
				//check if coins is offscreen
				if (mCoins[i]->GetPosition().x < (float)(mCoins[i]->GetCollisionBox().width * 0.5f) ||
					mCoins[i]->GetPosition().x > SCREEN_WIDTH - (float)(mCoins[i]->GetCollisionBox().width * 0.55f))
				{
					//mCoins[i].SetAlive(false);
					mScoreSystem->mScore += 100;
					std::cout << "Score: " << mScoreSystem->mScore << std::endl;
				}
			}

			//update coins
			mCoins[i]->Update(deltaTime, e);

			//check if coin collides with player
			if ((mCoins[i]->GetPosition().y > 300.0f || mCoins[i]->GetPosition().y <= 64.0f) &&
				(mCoins[i]->GetPosition().x > 64.0f || mCoins[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//coins collected
				coinIndexToDelete = i;
			}
		}

		//remove collected coins
		if (coinIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	mEnemies.push_back(mCharacterKoopa);
}

void GameScreenLevel::CreateCoins(Vector2D position)
{
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

	//CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	//CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	//CreateCoins(Vector2D(150, 32));

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
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
