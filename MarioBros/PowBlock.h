#pragma once

#include "SDL.h"
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	virtual void Render();
	SDL_Rect* GetCollisionBox();
	void TakeAHit();
	bool IsAvailable() { return mNumberOfHitsLeft > 0; }
private:
	SDL_Renderer* mRenderer;
	Vector2D* mPosition;
	Texture2D* mTexture;
	SDL_Rect* mRect;
	SDL_Rect* mDestRect;
	LevelMap* mLevelMap;
	bool powBlockAvailable = true;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int mNumberOfHitsLeft;
};