#include "CharacterCoin.h"

//constructor
CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	imagePath = "Images/Coin.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadTextureFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
}

//destructor
CharacterCoin::~CharacterCoin()
{
}

//update coin
void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		mFrameDelay = ANIMATION_DELAY;

		mCurrentFrame++;

		if (mCurrentFrame > 2)
		{
			mCurrentFrame = 0;
		}
	}
}

//render coin
void CharacterCoin::Render()
{
	int left = mSingleSpriteWidth * mCurrentFrame;

	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };
	
	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
}

