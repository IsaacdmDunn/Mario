#pragma once

//libraries
#include <SDL.h>
#include "Commons.h"

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	SCREENS GetScreenToChange() { return mScreenToChange; }

protected:
	SDL_Renderer* mRenderer;
	SCREENS mScreenToChange;
};