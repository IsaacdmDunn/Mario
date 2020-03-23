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
	void MarioDeath();

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mMarioDead = false;
	int mCurrentFrame;
	float mFrameDelay;

};