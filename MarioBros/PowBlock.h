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
	Rect2D GetCollisionBox() { return mRect; }
	void TakeAHit();
	bool IsAvailable() { return mNumberOfHitsLeft > 0; }
private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	Rect2D mRect;
	LevelMap* mLevelMap;
	bool powBlockAvailable = true;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int mNumberOfHitsLeft;
};