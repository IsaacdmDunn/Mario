#pragma once

#include "Character.h"

//class Texture2D;

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mCurrentFrame;
	float mFrameDelay;
};