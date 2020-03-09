#pragma once

#include <iostream>
#include "Commons.h"
#include <SDL.h>
#include "LevelMap.h"
#include "Texture2D.h"

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

	//bool IsJumping() { return mJumping; };
	void CancelJump();

	bool mJumping;

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	//virtual void MoveLeft(float deltaTime);
	//virtual void MoveRight(float deltaTime);

	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	bool mCanJump;
	float mJumpForce;
	int currentYPos;

	float mXVelocity;

	void AddGravity(float deltaTime);
	void Jump();

	float mCollisionRadius;

private:
	LevelMap* mCurrentLevelMap;
};

