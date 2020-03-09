#pragma once

#include "Character.h"
#include <SDL.h>
#include "Collisions.h"

class Texture2D;
class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

	void TakeDamage();
	void Jump();
	void SetAlive(bool mIsAlive);
	bool GetAlive() { return isAlive; }

private:
	void FlipRightWayUp();
	bool isAlive;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mMovementSpeed;
	bool mInjured;
	float mInjuredTime;
};
