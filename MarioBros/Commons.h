#pragma once

enum SCREENS
{
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

struct Vector2D
{
	float x;
	float y;
	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX , float initialY )
	{
		x = initialX;
		y = initialY;
	}
};

struct Rect2D
{
	float height;
	float width;
	float x;
	float y;

	Rect2D(float initialX = 0.0f, float initialY = 0.0f, float initialH = 0.0f, float initialW = 0.0f)
	{
		x = initialX;
		y = initialY;
		height = initialH;
		width = initialW;
	}
};
