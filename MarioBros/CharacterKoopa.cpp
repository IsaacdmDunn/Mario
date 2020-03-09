#include "CharacterKoopa.h"

//constructor
CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;

	//std::string imagePath = "Images/Koopa.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadTextureFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}
	mSingleSpriteWidth = mTexture->GetWidth();
	mSingleSpriteHeight = mTexture->GetHeight();
}

//destructor
CharacterKoopa::~CharacterKoopa()
{
}

//update koopa
void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	if (!mInjured)
	{
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if(mFacingDirection == FACING_RIGHT)
		{
			mMovingLeft = false;
			mMovingRight = true;
		}
	}
	else
	{
		mMovingLeft = false;
		mMovingRight = false;

		mInjuredTime -= deltaTime;

		if(mInjuredTime <= 0.0) 
		{
			FlipRightWayUp();
		}
	}
}

//render koopa
void CharacterKoopa::Render()
{
	int left = 0.0f;
	if (mInjured)
	{
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpriteSheet = {left, 0, mSingleSpriteWidth, mSingleSpriteHeight};

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

//koopa takes damage
void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = 2.5f;
	Jump();
}

//koopa jump
void CharacterKoopa::Jump()
{
	mJumpForce = JUMP_FORCE_INITIAL_SMALL;
	mJumping = true;
	mCanJump = false;
}

void CharacterKoopa::SetAlive(bool mIsAlive)
{
	isAlive = mIsAlive;
}

//flip koopa image
void CharacterKoopa::FlipRightWayUp()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mFacingDirection = FACING_LEFT;
	}
	else
	{
		FACING_RIGHT;
	}
}
