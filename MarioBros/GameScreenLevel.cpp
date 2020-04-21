//libraries
#include "GameScreenLevel.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "GameScreenManager.h"

//constructor
GameScreenLevel::GameScreenLevel(SDL_Renderer* renderer) : GameScreen(renderer) 
{
	coinIndexToDelete = -1;
	enemyIndexToDelete = -1;
	SetUpLevel();
	
	//plays level music
	mMusicSystem = new SoundManager();
	mMusicSystem->LoadMusic("Audio/Mario.mp3");
	mMusicSystem->PlayMusic();
}

//destructor
GameScreenLevel :: ~GameScreenLevel()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	
	for (int i = 0; i < LIVES_LEFT; i++)
	{
		mLives[i] = NULL;
	}
	delete[] mLives;

	delete mMario;
	mMario = NULL;
	delete mLuigi;
	mLuigi = NULL;

	delete mScoreSystem;
	mScoreSystem = NULL;

	delete mPowBlock;
	mPowBlock = NULL;
	mLevelMap = NULL;
	
	//clears vectors
	mEnemies.clear();
	mCoins.clear();
}

//renders game level
void GameScreenLevel::Render()
{
	//background texture
	mBackgroundTexture->Render(Vector2D(0.0, mBackgroundYPos), SDL_FLIP_NONE);

	//lives icon texture
	for (int i = 0; i < LIVES_LEFT; i++)
	{
		mLives[i]->Render(Vector2D(i * 20, mLivesIconYPos[i]), SDL_FLIP_NONE);
	}

	//powblock texture
	mPowBlock->Render();

	//player textures
	mMario->Render();
	mLuigi->Render();

	//enemy textures
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}
	
	//coin textures
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}
}

//updates level
void GameScreenLevel::Update(float deltaTime, SDL_Event e)
{
	//updates each object
	mMario->Update(deltaTime, e);
	mLuigi->Update(deltaTime, e);
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);
	UpdateLives();

	//if pow block was hit background texture will shake
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

	//check if mario is on screen
	if (mMario->GetPosition().y > SCREEN_HEIGHT)
	{
		//if mario is dead play death sound and set death state
		if (mMario->mMarioDead == false)
		{
			mMario->mMarioDead = true;
			mMusicSystem->LoadMusic("Audio/Mario.mp3");
			mMusicSystem->PlayMusic();
			
		}
		//if dead mario drops off screen remove a life and reset position
		if (mMario->GetPosition().y > 700)
		{
			mLivesSystem->mLives--;
			mMario->mMarioDead = false;
			mMario->SetPosition(Vector2D(64, 330));
			mMario->mJumping = false;
		}
		
	}
	//check if luigi is on screen
	else if (mLuigi->GetPosition().y > SCREEN_HEIGHT)
	{
		//if luigi is dead play death sound and set death state
		if (mLuigi->mLuigiDead == false)
		{
			mLuigi->mLuigiDead = true;
			mMusicSystem->LoadMusic("Audio/Mario.mp3");
			mMusicSystem->PlayMusic();
		}
		//if dead mario drops off screen remove a life and reset position
		if (mLuigi->GetPosition().y > 700)
		{
			mLivesSystem->mLives--;
			mLuigi->mLuigiDead = false;
			mLuigi->SetPosition(Vector2D(128, 330));
			mLuigi->mJumping = false;
		}
	}
}

//updates the pow block
void GameScreenLevel::UpdatePOWBlock()
{
	//checks for collisions between mario and powblock
	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), mMario->GetCollisionBox()) /*&& mPowBlock->IsAvailable*/)
	{
		//if mario was jumping while colliding then hit powblock
		if (mMario->mJumping == true)
		{
			ShakeScreen();
			mPowBlock->TakeAHit();
			mMario->CancelJump();
			mScoreSystem->mScore += 100;
			std::cout << "Score: " << mScoreSystem->mScore << std::endl;
			Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/PowBlock.wav");
			mMusicSystem->PlaySoundEffect(mSound);

			//makes all enemies take damage
			for (unsigned int i = 0; i < mEnemies.size(); i++)
			{
				mEnemies[i]->TakeDamage();
			}
		}
	}
	//checks for collisions between luigi and powblock
	else if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), mLuigi->GetCollisionBox()) /*&& mPowBlock->IsAvailable*/)
	{
		//if luigi was jumping while colliding then hit powblock
		if (mLuigi->mJumping == true)
		{
			ShakeScreen();
			mPowBlock->TakeAHit();
			mLuigi->CancelJump();
			mScoreSystem->mScore += 100;
			std::cout << "Score: " << mScoreSystem->mScore << std::endl;
			Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/PowBlock.wav");
			mMusicSystem->PlaySoundEffect(mSound);

			//makes all enemies take damage
			for (unsigned int i = 0; i < mEnemies.size(); i++)
			{
				mEnemies[i]->TakeDamage();
			}
		}
	}
}

//sets timer for how long the screen must shake
void GameScreenLevel::ShakeScreen()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
}

//updates enemies
void GameScreenLevel::UpdateEnemies(float deltaTime, SDL_Event e)
{
	//if enemies are in vector
	if (!mEnemies.empty())
	{
		//if the enemy is no longer alive then delete
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
			enemyIndexToDelete = -1;
		}

		//updates each enemy in vector
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//update enemy
			mEnemies[i]->Update(deltaTime, e);
			
			//check if enemies collides with mario
			if (Collisions::Instance()->Circle(mEnemies[i], mMario))
			{
				//if koopa is alive then kill mario
				if (mEnemies[i]->GetAlive() == true)
				{
					mMario->MarioDeath();
				}
				//if koopa is not alive then kill koopa and make kick sound
				else
				{
					Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/Kick.wav");
					mMusicSystem->PlaySoundEffect(mSound);
					enemyIndexToDelete = i;
				}
			}
			//check if enemies collides with luigi
			else if (Collisions::Instance()->Circle(mEnemies[i], mLuigi))
			{
				//if koopa is alive then kill luigi
				if (mEnemies[i]->GetAlive() == true)
				{
					mLuigi->LuigiDeath();
				}
				//if koopa is not alive then kill koopa and make kick sound
				else
				{
					Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/Kick.wav");
					mMusicSystem->PlaySoundEffect(mSound);
					enemyIndexToDelete = i;
				}
			}
		}
	}
	//if all enemies are dead then switch to level 2
	else
	{
		mScreenToChange = SCREEN_LEVEL2;
	}
}

//updates coins
void GameScreenLevel::UpdateCoins(float deltaTime, SDL_Event e)
{
	//if coins are in vector
	if (!mCoins.empty())
	{
		//remove collected coins
		if (coinIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
			coinIndexToDelete = -1;
		}
		//update each coin in vector
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			//if mario collides with coin add points, play coin sound and remove coin
			if (Collisions::Instance()->Box(mCoins[i]->GetCollisionBox(), mMario->GetCollisionBox()))
			{
				mScoreSystem->mScore += 100;
				coinIndexToDelete = i;
				Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/Coin.wav");
				mMusicSystem->PlaySoundEffect(mSound);
			}
			//if luigi collides with coin add points, play coin sound and remove coin
			else if (Collisions::Instance()->Box(mCoins[i]->GetCollisionBox(), mLuigi->GetCollisionBox()))
			{
				mScoreSystem->mScore += 100;
				coinIndexToDelete = i;
				Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/Coin.wav");
				mMusicSystem->PlaySoundEffect(mSound);
			}
			
			//update coins
			mCoins[i]->Update(deltaTime, e);
		}
	}
}

//create koopa
void GameScreenLevel::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	mCharacterKoopa = new CharacterKoopa(mRenderer, "Images/KoopaWalk.png" , position, mLevelMap, direction, speed);
	mEnemies.push_back(mCharacterKoopa);
}

//create coin
void GameScreenLevel::CreateCoins(Vector2D position)
{
	mCharacterCoin = new CharacterCoin(mRenderer, "Images/Coin.png", position, mLevelMap);
	mCoins.push_back(mCharacterCoin);
}

//update life counter
void GameScreenLevel::UpdateLives()
{
	//based on number of player lives set that number of life icons on screen
	if (mLivesSystem->mLives == 2)
	{
		mLivesIconYPos[2] = 1000.0f;
	}
	else if (mLivesSystem->mLives == 1)
	{
		mLivesIconYPos[1] = 1000.0f;
	}
	//if player has no lives then switch to gameover screen
	if (mLivesSystem->mLives == 0)
	{
		mLivesIconYPos[0] = 1000.0f;
		mScreenToChange = SCREEN_GAMEOVER;
	}
}

//set up level
bool GameScreenLevel::SetUpLevel()
{
	//set screen shake system to default
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	//setup the player character
	SetLevelMap();
	mMario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	mLuigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(128, 330), mLevelMap);

	//add life and score systems
	mScoreSystem = new ScoreSystem();
	mLivesSystem = new LivesSystem();

	//create koopa and coins on the level
	CreateKoopa(Vector2D(160, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(320, 32), FACING_LEFT, KOOPA_SPEED);
	CreateCoins(Vector2D(160, 128));
	CreateCoins(Vector2D(192, 128));
	CreateCoins(Vector2D(224, 128));
	CreateCoins(Vector2D(256, 128));
	CreateCoins(Vector2D(288, 128));
	CreateCoins(Vector2D(320, 128));

	//Set up POW block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);


	//Load the background Texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadTextureFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture";
		return false;
	}

	//load texture for life icons
	for (int i = 0; i < LIVES_LEFT; i++)
	{
		mLives[i] = new Texture2D(mRenderer);
		if (!mLives[i]->LoadTextureFromFile("Images/LivesIcon.png"))
		{
			std::cout << "Failed to load texture";
			return false;
		}
	}
	return false;
}

//set level map
void GameScreenLevel::SetLevelMap()
{
	//0 is nothing, 1 is floor/walls and 2 is pow block
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
