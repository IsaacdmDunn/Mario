//libraies
#include "PowBlock.h"
#include <iostream>

//constructor
PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* levelMap)
{
	std::string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadTextureFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}
	mLevelMap = levelMap;

	//gets sprite dimensions by dividing texture width by number of frames
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;

	//sets pow block position on level
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);

}

//destructor
PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}

//renders the pow block
void PowBlock::Render()
{
	//if the pow block isnt used up then render
	if (mNumberOfHitsLeft > 0)
	{
		//Get the portion of the spritesheet you want to draw
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		// positions
		SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		//Determine where you want it drawn
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		//Draw
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	//if pow block is used up render off screen to move the collision
	else
	{
		mPosition.x = 1000;
	}
}

//gets collision box for pow block
Rect2D PowBlock::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mTexture->GetHeight());
}

//pow block will take damage and when used up will remove collsision box
void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft -= 1;
	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;

		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}
