#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "Collisions.h"

//constructor
Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{

	mCollisionRadius = 15.0f;
	mCurrentLevelMap = map;
	mFacingDirection = FACING_RIGHT;

	//mFacingDirection = FACING_RIGHT;
	mRenderer = renderer;
	mPosition = startPosition;
	//SetPosition(startPosition);
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadTextureFromFile(imagePath);

	mMusicSystem = new SoundManager();
}

//destructor
Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	//render character to face a direction
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, 180.0f);
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE, 180.0f);
	}

}

//update characters
void Character::Update(float deltaTime, SDL_Event e)
{


	//sets previous position of character
	float newXPos = GetPosition().x;
	float newYPos = GetPosition().y;

	//if character is jumping
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

	//updates x-position using velocity of character
	if (mXVelocity != 0.0f) {
		newXPos += mXVelocity * deltaTime;
	}

	//limits character velocity
	if (mXVelocity > PLAYER_VELOCITY_CAP)
	{
		mXVelocity = PLAYER_VELOCITY_CAP;
	}
	else if (mXVelocity < -PLAYER_VELOCITY_CAP)
	{
		mXVelocity = -PLAYER_VELOCITY_CAP;
	}

	CheckCollisions(newXPos, newYPos, deltaTime);

	


}

void Character::CheckCollisions(float newXPos, float newYPos, float deltaTime)
{
	//finds tiles around player
	int leftTile = newXPos / TILE_WIDTH;
	int rightTile = (newXPos + (mTexture->GetWidth() / mNumberOfFrames)) / TILE_WIDTH;
	int topTile = newYPos / TILE_HEIGHT;
	int bottomTile = (newYPos + mTexture->GetHeight()) / TILE_HEIGHT;


	//left collision
	if (mCurrentLevelMap->GetTileAt(bottomTile - 1, leftTile) == 1) {
		newXPos = GetPosition().x;
	}

	//right collision
	if (mCurrentLevelMap->GetTileAt(bottomTile - 1, rightTile) == 1) {
		newXPos = GetPosition().x;
	}

	//foot collision
	if ((mCurrentLevelMap->GetTileAt(bottomTile, rightTile) == 1 || mCurrentLevelMap->GetTileAt(bottomTile, leftTile) == 1)) {
		mCanJump = true;
		mOnFloor = true;
	}
	//update y-position using gravity
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

	//restricts X Position
	if (newXPos < 0.0f || newXPos + (mTexture->GetWidth()/mNumberOfFrames) > SCREEN_WIDTH) {
		newXPos = GetPosition().x;
	}

	//restricts Y Position
	if (newYPos < 0.0f || newYPos + mTexture->GetHeight() > SCREEN_HEIGHT) {
		newYPos = GetPosition().y + 1;
		mJumpForce = 0.0f;
	}

	SetPosition(Vector2D(newXPos, newYPos));
}

//set character's new position
void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

//get character's position
Vector2D Character::GetPosition()
{
	return mPosition;
}

//updates y-position using gravity
void Character::AddGravity(float deltaTime)
{

	mPosition.y += GRAVITY * deltaTime;

}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, (mTexture->GetWidth()/mNumberOfFrames), mTexture->GetHeight());

}

//sets jumping force when player jumps
void Character::Jump()
{

	mCanJump = false;
	if (!mJumping)
	{

		Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/Jump.wav");
		mMusicSystem->PlaySoundEffect(mSound);
		mJumpForce = JUMP_FORCE_INITIAL;
		mJumping = true;

	}
}

//gets borders for character collision
float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

//cancels jump
void Character::CancelJump()
{
	mJumpForce = 0;
}

