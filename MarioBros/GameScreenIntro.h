#pragma once

//libraries
#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include "ScoreSystem.h"
#include "SoundManager.h"

class Texture2D;

class GameScreenIntro : GameScreen
{
public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();
	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;
	Texture2D* mIntroText;
	ScoreSystem* mScoreSystem;
	SoundManager* mMusicSystem;

	bool SetUpLevel();

};