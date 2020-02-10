#include "CharacterLuigi.h"
#include "Texture2D.h"
#include "Constants.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : Character(renderer, imagePath, startPosition)
{
	//mJumping = false;
	//mCanJump = true;

	////mFacingDirection = FACING_RIGHT;
	//mRenderer = renderer;
	//SetPosition(startPosition);
	//mTexture = new Texture2D(mRenderer);
	//mTexture->LoadTextureFromFile(imagePath);
}

CharacterLuigi::~CharacterLuigi()
{
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	Character::AddGravity(deltaTime);

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	//player controls
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Jump();
		case SDLK_d:
			mMovingRight = false;
		case SDLK_a:
			mMovingLeft = false;

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



