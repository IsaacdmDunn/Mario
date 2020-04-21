#pragma once

//struct for a 2D vector using x, y values
struct Vector2D
{
	float x;
	float y;

	Vector2D(float initialX = 0.0f, float initialY = 0.0f) {
		x = initialX;
		y = initialY;
	}
};

//struct for a 2D Rect using x, y, height, width
struct Rect2D
{
	float x;
	float y;
	int width;
	int height;

	Rect2D(float initialX = 0.0f, float initialY = 0.0f, int initialWidth = 0.0f, int initialHeight = 0.0f) {
		x = initialX;
		y = initialY;
		width = initialWidth;
		height = initialHeight;
	}
};

//enum for the different screens in the game
enum SCREENS {
	SCREEN_NULL = 0,
	SCREEN_INTRO,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
};

//enum for the different ways a character can face
enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};


