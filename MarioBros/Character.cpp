#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "Collisions.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	mJumping = false;
	mCanJump = true;

	

	mCollisionRadius = 15.0f;
	mCurrentLevelMap = map;

	//mFacingDirection = FACING_RIGHT;
	mRenderer = renderer;
	mPosition = startPosition;
	//SetPosition(startPosition);
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadTextureFromFile(imagePath);
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, 180.0f);
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE, 180.0f);
	}
	
}

void Character::Update(float deltaTime, SDL_Event e)
{
	//Deal with Jumping first
	if (mJumping)
	{
		//adjust the position
		mPosition.y -= mJumpForce * deltaTime;

		//reduce jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		
		////check jump force rediced to 0
		//if (mPosition.y > 330.0f)
		//{
		//	mPosition.y = 330.0f;

		//	//collided with ground allowing player to jump
		//	mCanJump = true;
		//}
		if (mJumpForce <= 0.0f)
		{
			mJumping = false;
		}
	}
	else 
	{
		currentYPos = mPosition.y;
	}
	int centralXPosition = mPosition.x / TILE_WIDTH;
	int footPosition = (mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
	std::cout << footPosition << std::endl;
	/* (int)(mPosition.x+(mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;*/
		/*(int)(mPosition.y+(mTexture->GetHeight() * 0.5f)) / TILE_HEIGHT;*/
	//check if player is currently in the air
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		std::cout << mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) << std::endl;
		AddGravity(deltaTime);
	}
	else if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 1)
	{
		currentYPos = mPosition.y;
		mPosition.y = currentYPos;
		//Collided with ground allowing player to jump again
		mCanJump = true;
		mJumping = false;
	}
	
	

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	//player controls
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Jump();
		case SDLK_d:
			mMovingRight = false;
		case SDLK_a:
			mMovingLeft = false;
		
		}
		
	default:
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			mMovingRight = true;
			break;
		case SDLK_a:
			mMovingLeft = true;
			break;
		default:
			break;
		}
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::MoveLeft(float deltaTime)
{
	mPosition.x -= PLAYER_SPEED * deltaTime;

	mFacingDirection = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	mPosition.x += PLAYER_SPEED * deltaTime;

	mFacingDirection = FACING_RIGHT;
}

void Character::AddGravity(float deltaTime)
{
	
	mPosition.y += GRAVITY * deltaTime;
	
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = JUMP_FORCE_INITIAL;
		mJumping = true;
		mCanJump = false;

	}
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

