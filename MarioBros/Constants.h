#pragma once

//screen dimensions
#define SCREEN_WIDTH	512
#define SCREEN_HEIGHT	416

//map tile system definitions
#define MAP_HEIGHT		13
#define MAP_WIDTH		16
#define TILE_HEIGHT		32
#define TILE_WIDTH		32

//player movement definitions
#define PLAYER_SPEED			55.0f
#define PLAYER_VELOCITY_CAP		150.0f
#define JUMP_FORCE_DECREMENT	300.0f
#define JUMP_FORCE_INITIAL		375.0f
#define GRAVITY					96.0f

//duration of POW block screen wobble
#define SCREENSHAKE_DURATION    0.25f

//koopa definitions
#define INJURED_TIME				10.0f
#define JUMP_FORCE_INITIAL_SMALL	250.0f
#define KOOPA_SPEED					0.017f
#define KOOPA_RESPAWN_RATE			5.0f

//coin definitions
#define ANIMATION_DELAY				0.15f
