#pragma once

#include "commons.h"

#include "SDL.h"

class Character;

class Collisions
{
public:
	
	~Collisions();

	static Collisions* Instance();

	bool Circle(Character* character1, Character* character2);
	bool Box(SDL_Rect* rect1, SDL_Rect* rect2);

	//void SetPosition(Vector2D newPosition);
	//double GetCollisionRadius();

private:
	Collisions();

	static Collisions* mInstance;
};

