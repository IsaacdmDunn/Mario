#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;

	mSingleSpriteHeight = mTexture->GetHeight();
	mSingleSpriteWidth = mTexture->GetWidth() / 2;
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
}

void CharacterKoopa::Render()
{
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = 2.5f;
	Jump();
}

void CharacterKoopa::Jump()
{
	mJumpForce = JUMP_FORCE_INITIAL_SMALL;
	mJumping = true;
	mCanJump = false;
}

void CharacterKoopa::FlipRightWayUp()
{
}
