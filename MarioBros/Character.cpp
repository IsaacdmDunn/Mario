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

		
	}
	else 
	{
		currentYPos = mPosition.y;
	}
	int centralXPosition = mPosition.x / TILE_WIDTH;
	int footPosition = (mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
	int topPosition = (mPosition.y) / TILE_HEIGHT;
	
	float newXPos = GetPosition().x;
	float newYPos = GetPosition().y;


	if (mJumping) {
		mCanJump = false;

		//adjusts position
		newYPos -= mJumpForce * deltaTime;

		//reduces jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f) {
			mJumping = false;
		}
	}

	if (mXVelocity != 0.0f) {
		newXPos += mXVelocity * deltaTime;
	}


	int leftTile = newXPos / TILE_WIDTH;
	int rightTile = (newXPos + mTexture->GetWidth()) / TILE_WIDTH;
	int topTile = newYPos / TILE_HEIGHT;
	int bottomTile = (newYPos + mTexture->GetHeight()) / TILE_HEIGHT;


	//left collision
	if (mCurrentLevelMap->GetTileAt(bottomTile - 1, leftTile) != 0) {
		newXPos = GetPosition().x;
	}

	//right collision
	if (mCurrentLevelMap->GetTileAt(bottomTile - 1, rightTile) != 0) {
		newXPos = GetPosition().x;
	}

	//foot collision
	if ((mCurrentLevelMap->GetTileAt(bottomTile, rightTile) != 0 || mCurrentLevelMap->GetTileAt(bottomTile, leftTile) != 0)) {
		mCanJump = true;
	}
	else {
		newYPos += GRAVITY * deltaTime;
	}



	//head collision
	if (mCurrentLevelMap->GetTileAt(topTile, rightTile) == 1) {
		mJumpForce = 0.0f;
	}
	if (mCurrentLevelMap->GetTileAt(topTile, leftTile) == 1) {
		mJumpForce = 0.0f;
	}

	//restrict Mario's X Position
	if (newXPos < 0.0f || newXPos + mTexture->GetWidth() > SCREEN_WIDTH) {
		newXPos = GetPosition().x;
	}

	//restrict Mario's Y Position
	if (newYPos < 0.0f || newYPos + mTexture->GetHeight() > SCREEN_HEIGHT) {
		newYPos = GetPosition().y + 1;
		mJumpForce = 0.0f;
	}


	SetPosition(Vector2D(newXPos, newYPos));

	if (mMovingLeft)
	{
		mXVelocity -= 0.1f;
		//MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		mXVelocity +=0.1f;
		//MoveRight(deltaTime);
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

void Character::CancelJump()
{
	mJumpForce = 0;
}

