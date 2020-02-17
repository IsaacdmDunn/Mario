#pragma once

#include "commons.h"

class Character;

class Collisions
{
public:
	
	~Collisions();

	static Collisions* Instance();

	bool Circle(Character* character1, Character* character2);
	bool Box(Rect2D rect1, Rect2D rect2);

	//void SetPosition(Vector2D newPosition);
	//double GetCollisionRadius();

private:
	Collisions();

	static Collisions* mInstance;
};

