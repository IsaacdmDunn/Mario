#pragma once

//libraries
#include "Character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;
	void LuigiDeath();

	bool mLuigiDead = false;

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int mCurrentFrame;
	float mFrameDelay;
};