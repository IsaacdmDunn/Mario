#pragma once

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"
#include "LevelMap.h"

class Texture2D;
class PowBlock;

class GameScreenLevel : GameScreen
{
public:
	GameScreenLevel(SDL_Renderer* renderer);
	~GameScreenLevel();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePowBlock();
	void ShakeScreen();
private:
	Texture2D* mBackgroundTexture;
	CharacterLuigi* Luigi;
	CharacterMario* Mario;

	bool SetUpLevel();

	void SetLevelMap();

	LevelMap* mLevelMap;

	PowBlock* mPowBlock;
	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
};