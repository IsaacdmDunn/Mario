#pragma once

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"

class Texture2D;

class GameScreenLevel : GameScreen
{
public:
	GameScreenLevel(SDL_Renderer* renderer);
	~GameScreenLevel();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;
	Character* Luigi;

	bool SetUpLevel();
};