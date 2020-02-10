#pragma once

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"

class Texture2D;
class Character;

class GameScreenLevel : GameScreen
{
public:
	GameScreenLevel(SDL_Renderer* renderer);
	~GameScreenLevel();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;
	CharacterLuigi* Luigi;
	CharacterMario* Mario;

	bool SetUpLevel();

	/*Character* mCharacter1;
	Character* mCharacter2;
	Character* mLuigiCharacter;
	Character* mMarioCharacter;*/
};