#include "CharacterMario.h"
#include "Texture2D.h"
#include "Constants.h"

//constructer
CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mPosition = startPosition;

	imagePath = "Images/MarioWalk.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadTextureFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}
	mNumberOfFrames = 7;
	mSingleSpriteWidth = mTexture->GetWidth() / mNumberOfFrames;
	mSingleSpriteHeight = mTexture->GetHeight();
	mCollisionRadius = 16;
}

//destructer
CharacterMario::~CharacterMario()
{
}

//update
void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	if (mMovingLeft == true || mMovingRight == true)
	{
		mFrameDelay -= deltaTime;
		if (mFrameDelay <= 0.0f)
		{
			mFrameDelay = ANIMATION_DELAY;

			mCurrentFrame++;

			if (mCurrentFrame > 5)
			{
				mCurrentFrame = 0;
			}
		}
	}
	//if player jumps use jumping animation else if player is no longer jumping reset player position
	if (mJumping == true && mOnFloor == true)
	{
		mCurrentFrame = 6;
	}
	else if (mCurrentFrame > 5 && mOnFloor == true)
	{
		mCurrentFrame = 0;
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
			mXVelocity = 0;
			mCurrentFrame = 0;
		case SDLK_a:
			mMovingLeft = false;
			mXVelocity = 0;
			mCurrentFrame = 0;
		}

	default:
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			mMovingRight = true;
			mMovingLeft = false;
			mFacingDirection = FACING_RIGHT;
			break;
		case SDLK_a:
			mMovingLeft = true;
			mMovingRight = false;
			mFacingDirection = FACING_LEFT;
			break;
		default:
			break;
		}
	}
	//sets previous position of character
	float newXPos = GetPosition().x;
	float newYPos = GetPosition().y;
	//update
	Character::Update(deltaTime, e);
	if (mMarioDead == true)
	{

		Character::CheckCollisions(newXPos, newYPos, deltaTime);
	}

	//checks if player is moving then add velocity
	if (mMovingLeft)
	{
		mXVelocity -= 0.1f;
	}
	else if (mMovingRight)
	{
		mXVelocity += 0.1f;
	}
}

void CharacterMario::Render()
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

void CharacterMario::MarioDeath()
{
	if (!mJumping)
	{
		mMusicSystem->PauseMusic();
		Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/MarioDeath.wav");
		mMusicSystem->PlaySoundEffect(mSound);
		mJumpForce = JUMP_FORCE_INITIAL;
		mJumping = true;
		mMarioDead = true;
	}
}






