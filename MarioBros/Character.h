#pragma once

#include <iostream>
#include "Commons.h"
#include <SDL.h>
//#include "Collisions.h"
//#include "Texture2D.h"

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~Character();
	virtual void Render(); 
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();


	Rect2D GetCollisionBox();

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	void AddGravity(float deltaTime);
	void Jump();


	float mCollisionRadius;

private:
};

