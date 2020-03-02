#include "CharacterKoopa.h"

//constructor
CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;

	mSingleSpriteHeight = mTexture->GetHeight();
	mSingleSpriteWidth = mTexture->GetWidth() / 2;
}

//destructor
CharacterKoopa::~CharacterKoopa()
{
}

//update koopa
void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
}

//render koopa
void CharacterKoopa::Render()
{
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

//flip koopa image
void CharacterKoopa::FlipRightWayUp()
{
}
