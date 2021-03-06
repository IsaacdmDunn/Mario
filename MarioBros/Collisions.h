#pragma once
#ifndef _COLLISIONS
#define _COLLISIONS

//libraries
#include "SDL.h"
#include "Commons.h"
#include "Character.h"

class Character;

class Collisions
{
public:

	~Collisions();
	static Collisions* Instance();

	bool Box(Rect2D rect1, Rect2D rect2);
	bool Circle(Character* character1, Character* character2);
private:
	Collisions();
	static Collisions* mInstance;
};

#endif