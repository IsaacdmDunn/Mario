#include "PowBlock.h"
#include <iostream>

//constructer
PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	//gets texture
	std::string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadTextureFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture: " << imagePath << std::endl;
		return;
	}

	mLevelMap = map;

	//splits up texture into sprites from sprite sheet
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = new Vector2D((SCREEN_WIDTH * 0.5) - mSingleSpriteWidth * 0.5f, 256);

	//sets up the rect for the POW block
	mDestRect = new SDL_Rect();
	mDestRect->x = mPosition->x;
	mDestRect->y = mPosition->y;
	mDestRect->w = mSingleSpriteWidth;
	mDestRect->h = mSingleSpriteHeight;

	mRect = new SDL_Rect();
	mRect->x = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);
	mRect->y = 0;
	mRect->w = TILE_WIDTH;
	mRect->h = TILE_HEIGHT;

	
}

//destructor
PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;

}

//renders sprite
void PowBlock::Render()
{
	if (mNumberOfHitsLeft >= 0)
	{
		mTexture->Render(mRect, mDestRect, SDL_FLIP_NONE, 0.0f);
	}
}

//sets borders for collision
SDL_Rect* PowBlock::GetCollisionBox()
{
	SDL_Rect collisionBox = SDL_Rect();
	collisionBox = { (int)mPosition->x, (int)mPosition->y,(int) mSingleSpriteWidth,(int) mSingleSpriteHeight };
	return&collisionBox;
}

//tracks number of POW block collisions and changes sprite 
void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft--;
	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;

		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}
