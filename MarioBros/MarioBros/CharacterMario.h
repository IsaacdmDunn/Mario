#pragma once

#include "Character.h"

//class Texture2D;

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mCurrentFrame;
	float mFrameDelay;
	int previousFrame = 0;

};