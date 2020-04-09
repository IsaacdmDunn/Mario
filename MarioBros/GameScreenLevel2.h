#pragma once

#include <SDL.h>
#include <vector>
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"
#include "PowBlock.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "ScoreSystem.h"
#include "SoundManager.h"

class Texture2D;
class PowBlock;

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePOWBlock();
	void ShakeScreen();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoins(Vector2D position);
private:
	Texture2D* mBackgroundTexture;
	CharacterLuigi* Luigi;
	CharacterMario* Mario;

	CharacterKoopa* mCharacterKoopa;
	CharacterCoin* mCharacterCoin;
	std::vector<CharacterKoopa*> mEnemies;
	int enemyIndexToDelete;
	std::vector<CharacterCoin*> mCoins;
	int coinIndexToDelete;

	ScoreSystem* mScoreSystem;
	SoundManager* mMusicSystem;

	bool SetUpLevel();
	void SetLevelMap();

	LevelMap* mLevelMap;
	PowBlock* mPowBlock;
	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;

	float mEnemyRespawnTime;
};