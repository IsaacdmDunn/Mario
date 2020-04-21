#pragma once
#ifndef _POW_BLOCK_H
#define _POW_BLOCK_H

//libraries
#include <SDL.h>
#include "Collisions.h"
#include "LevelMap.h"
#include "Texture2D.h"

class Texture2D;
class LevelMap;

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* levelMap);
	~PowBlock();
	void Render();
	void TakeAHit();
	Rect2D GetCollisionBox();
	

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int mNumberOfHitsLeft;
};

#endif