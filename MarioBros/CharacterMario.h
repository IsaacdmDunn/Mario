#pragma once

//libraries
#include "Character.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;
	void MarioDeath();
	bool mMarioDead = false;

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int mCurrentFrame;
	float mFrameDelay;

};