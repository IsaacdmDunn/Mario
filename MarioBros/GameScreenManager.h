#pragma once

//libraries
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenLevel.h"
#include "GameScreenLevel2.h"
#include "GameScreenIntro.h"
#include "GameScreenGameOver.h"

class GameScreen;

class GameScreenManager {
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void ChangeScreen(SCREENS newScreen);

private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;

};
