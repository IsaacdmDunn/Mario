#pragma once

#include <iostream>
#include "Commons.h"
#include <SDL.h>
#include "LevelMap.h"
#include "Texture2D.h"
#include "SoundManager.h"

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
	float GetCollisionRadius();

	Rect2D GetCollisionBox();

	void CancelJump();

	bool mJumping;

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	SoundManager* mMusicSystem;


	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	bool mCanJump;
	float mJumpForce;
	int currentYPos;

	float mXVelocity;

	void AddGravity(float deltaTime);
	void CheckCollisions(float newXPos, float newYPos, float deltaTime);
	void Jump();

	float mCollisionRadius;
	int mNumberOfFrames;
	bool mOnFloor;

	Mix_Chunk* mSound;

private:
	LevelMap* mCurrentLevelMap;
};

