//libraries
#include "CharacterKoopa.h"

//constructor
CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadTextureFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}

	//sets up values
	mInjured = false;
	isAlive = true;
	mCollisionRadius = 16;

	//gets sprite dimensions by dividing texture width by number of frames
	mNumberOfFrames = 9;
	mSingleSpriteWidth = mTexture->GetWidth() / mNumberOfFrames;
	mSingleSpriteHeight = mTexture->GetHeight();
}

//destructor
CharacterKoopa::~CharacterKoopa()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
}

//update koopa
void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//if koopa is not injured
	if (!mInjured)
	{
		//cycles through koopa walk animation
		mFrameDelay -= deltaTime;
		if (mFrameDelay <= 0.0f)
		{
			mFrameDelay = ANIMATION_DELAY;

			mCurrentFrame++;

			if (mCurrentFrame > 7)
			{
				mCurrentFrame = 0;
			}
		}

		//moves koopa in a direction
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
			mPosition.x += KOOPA_SPEED;
		}
		else if(mFacingDirection == FACING_RIGHT)
		{
			mMovingLeft = false;
			mMovingRight = true;
			mPosition.x -= KOOPA_SPEED;
		}
	}
	//if koopa is injured set to injured sprite and stop movement until timer is set off
	else
	{
		mCurrentFrame = 8;
		mMovingLeft = false;
		mMovingRight = false;

		mInjuredTime -= deltaTime;
		if(mInjuredTime <= 0.0) 
		{
			FlipRightWayUp();
		}
	}

	//update character and collisions
	Character::Update(deltaTime, e);

	//if koopa hits left or right side of screen then make koopa walk the other direction
	if (mPosition.x < 0)
	{
		mFacingDirection = FACING_LEFT;
		mPosition.x = 0;
	}
	else if (mPosition.x > SCREEN_WIDTH - mSingleSpriteWidth)
	{
		mFacingDirection = FACING_RIGHT;
		mPosition.x = SCREEN_WIDTH - mSingleSpriteWidth;
	}

}

//render koopa using sprite
void CharacterKoopa::Render()
{
	
	int left = mSingleSpriteWidth * mCurrentFrame;
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	//render character to face a direction
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
}

//koopa takes damage
void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	isAlive = false;
	Jump();
}

//koopa jump
void CharacterKoopa::Jump()
{
	mJumpForce = JUMP_FORCE_INITIAL_SMALL;
	mJumping = true;
	mCanJump = false;
}

//sets whether koopa alive state
void CharacterKoopa::SetAlive(bool mIsInjured)
{
	mInjured = mIsInjured;
}

//flip koopa image back up and turns movement back on
void CharacterKoopa::FlipRightWayUp()
{
	mCurrentFrame = 0;
	isAlive = true;
	mInjured = false;
	mMovingLeft = true;
	mMovingRight = true;
}
