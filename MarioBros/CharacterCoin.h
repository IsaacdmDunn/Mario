#pragma once

#include "Character.h"
#include <SDL.h>
#include "Collisions.h"

class Texture2D;
class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float movementSpeed);
	~CharacterCoin();

	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mMovementSpeed;

	int mCurrentFrame;
	float mFrameDelay;
};
