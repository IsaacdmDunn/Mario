#pragma once

//libraries
#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include "ScoreSystem.h"
#include "SoundManager.h"

class Texture2D;

class GameScreenGameOver : GameScreen
{
public:
	GameScreenGameOver(SDL_Renderer* renderer);
	~GameScreenGameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;
	Texture2D* mIntroText;
	Texture2D* mGameOverText;
	ScoreSystem* mScoreSystem;
	SoundManager* mMusicSystem;

	bool SetUpLevel();
};