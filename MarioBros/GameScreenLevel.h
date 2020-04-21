#pragma once

//libraries
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
#include "LivesSystem.h"
#include "SoundManager.h"

class Texture2D;
class PowBlock;

class GameScreenLevel : GameScreen
{
public:
	GameScreenLevel(SDL_Renderer* renderer);
	~GameScreenLevel();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePOWBlock();
	void ShakeScreen();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoins(Vector2D position);
	void UpdateLives();

private:
	Texture2D* mBackgroundTexture;
	Texture2D* mLives[LIVES_LEFT];
	int mLivesIconYPos[LIVES_LEFT];
	CharacterLuigi* mLuigi;
	CharacterMario* mMario;

	CharacterKoopa* mCharacterKoopa;
	CharacterCoin* mCharacterCoin;
	std::vector<CharacterKoopa*> mEnemies;
	int enemyIndexToDelete;
	std::vector<CharacterCoin*> mCoins;
	int coinIndexToDelete;

	ScoreSystem* mScoreSystem;
	LivesSystem* mLivesSystem;
	SoundManager* mMusicSystem;

	bool SetUpLevel();
	void SetLevelMap();

	LevelMap* mLevelMap;
	PowBlock* mPowBlock;
	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
};