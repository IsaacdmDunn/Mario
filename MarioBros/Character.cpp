#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	mJumping = false;
	mCanJump = true;

	mCollisionRadius = 15.0f;

	//mFacingDirection = FACING_RIGHT;
	mRenderer = renderer;
	mPosition = startPosition;
	//SetPosition(startPosition);
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadTextureFromFile(imagePath))
	{
		std::cout << "failed to load" << std::endl;
	}
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
	AddGravity(deltaTime);

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
			mMovingLeft = false;
			break;
		case SDLK_a:
			mMovingLeft = true;
			mMovingRight = false;
			break;
		default:
			break;
		}
	}
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
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
	mPosition.x -= PLAYER_SPEED;

	mFacingDirection = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	mPosition.x += PLAYER_SPEED;

	mFacingDirection = FACING_RIGHT;
}

void Character::AddGravity(float deltaTime)
{
	//Deal with Jumping first
	if (mJumping)
	{
		
		//adjust the position
		mPosition.y -= mJumpForce * deltaTime;

		//reduce jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//check jump force rediced to 0
		if (mPosition.y > 330.0f)
		{
			mPosition.y = 330.0f;
			mJumping = false;

			//collided with ground allowing player to jump
			mCanJump = true;
		}
	}
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

Rect2D Character::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}