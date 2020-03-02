#pragma once

#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

	void TakeDamage();
	void Jump();

private:
	void FlipRightWayUp();

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mMovementSpeed;
	bool mInjured;
	float mInjuredTime;
};
