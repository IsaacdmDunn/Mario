#include "CharacterLuigi.h"
#include "Texture2D.h"
#include "Constants.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mPosition = startPosition;

	imagePath = "Images/LuigiWalk.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadTextureFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}
	mNumberOfFrames = 6;
	mSingleSpriteWidth = mTexture->GetWidth() / mNumberOfFrames;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterLuigi::~CharacterLuigi()
{
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
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

	//player controls
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			Jump();
		case SDLK_RIGHT:
			mMovingRight = false;
			mXVelocity = 0;
			mCurrentFrame = 0;
			break;
		case SDLK_LEFT:
			mMovingLeft = false;
			mXVelocity = 0;
			mCurrentFrame = 0;
			break;
		}

	default:
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
			mMovingRight = true;
			mMovingLeft = false;
			mFacingDirection = FACING_RIGHT;
			break;
		case SDLK_LEFT:
			mMovingLeft = true;
			mMovingRight = false;
			mFacingDirection = FACING_LEFT;
			break;
		default:
			break;
		}
	}

	Character::Update(deltaTime, e);
}

void CharacterLuigi::Render()
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




