#include "CharacterMario.h"
#include "Texture2D.h"
#include "Constants.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	//mJumping = false;
	//mCanJump = true;

	////mFacingDirection = FACING_RIGHT;
	//mRenderer = renderer;
	//SetPosition(startPosition);
	//mTexture = new Texture2D(mRenderer);
	//mTexture->LoadTextureFromFile(imagePath);
}

CharacterMario::~CharacterMario()
{
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	//player controls
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Jump();
		case SDLK_d:
			mMovingRight = false;
			mXVelocity = 0;
		case SDLK_a:
			mMovingLeft = false;
			mXVelocity = 0;
		}

	default:
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			mMovingRight = true;
			mMovingLeft = false;
			break;
		case SDLK_a:
			mMovingLeft = true;
			mMovingRight = false;
			break;
		default:
			break;
		}
	}

	Character::Update(deltaTime, e);
}





