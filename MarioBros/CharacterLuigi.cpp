#include "CharacterLuigi.h"
#include "Texture2D.h"
#include "Constants.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
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
	//Character::AddGravity(deltaTime);

	//if (mMovingLeft)
	//{
	//	MoveLeft(deltaTime);
	//}
	//else if (mMovingRight)
	//{
	//	MoveRight(deltaTime);
	//}

	//player controls
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			Jump();
		case SDLK_RIGHT:
			mMovingRight = false;
			mXVelocity = 0;
			break;
		case SDLK_LEFT:
			mMovingLeft = false;
			mXVelocity = 0;
			break;
		}

	default:
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
			mMovingRight = true;
			mMovingLeft = false;
			mFacingDirection = FACING_RIGHT;
			break;
		case SDLK_LEFT:
			mMovingLeft = true;
			mMovingRight = false;
			mFacingDirection = FACING_LEFT;
			break;
		default:
			break;
		}
	}

	Character::Update(deltaTime, e);
}




