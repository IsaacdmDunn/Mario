//library
#include "Collisions.h"

Collisions* Collisions::mInstance = NULL;

//takes 2 collision boxes and checks if they have collided return true
bool Collisions::Box(Rect2D rect1, Rect2D rect2) {
	if (rect1.x + (rect1.width / 2) > rect2.x&&
		rect1.x + (rect1.width / 2) < rect2.x + rect2.width &&
		rect1.y + (rect1.height / 2) > rect2.y&&
		rect1.y + (rect1.height / 2) < rect2.y + rect2.height)
	{
		return true;
	}

	return false;

}

//takes 2 characters and checks if they have collided return true
bool Collisions::Circle(Character* character1, Character* character2)
{
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x),
		(character1->GetPosition().y - character2->GetPosition().y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double character1Radius = character1->GetCollisionRadius();
	double character2Radius = character2->GetCollisionRadius();
	double combinedDistance = character1Radius + character2Radius;

	return distance < combinedDistance;
	return false;
}

//constructor
Collisions::Collisions()
{
}

//destructor
Collisions::~Collisions()
{
	mInstance = NULL;
}

//creates an instance for collision
Collisions* Collisions::Instance()
{
	if (!mInstance)
	{
		mInstance = new Collisions;
	}
	return mInstance;
}
