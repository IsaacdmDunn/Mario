#pragma once


struct Vector2D
{
	float x;
	float y;

	Vector2D(float initialX = 0.0f, float initialY = 0.0f) {
		x = initialX;
		y = initialY;
	}


};

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

enum SCREENS {
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};


