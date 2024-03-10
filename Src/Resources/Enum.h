#pragma once

enum PIXEL_TYPE
{
	PIXEL_SOLID			= 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF			= 0x2592,
	PIXEL_QUARTER		= 0x2591,
};

enum KEY_VALUE
{
	UP		= 72,
	DOWN	= 80,
	LEFT	= 75,
	RIGHT	= 77
};

enum CHARACTER_TYPE
{
	PLAYER	= 1,
	ENEMY	= 2,
	OBJECT	= 4
};

enum DIRECTION
{
	FACE_UP		= 1,
	FACE_DOWN	= 2,
	FACE_LEFT	= 3,
	FACE_RIGHT	= 4
};

enum GROUP_LABEL : std::size_t
{
	groupMap,
	groupPlayers,
	groupColliders,
	groupProjectiles
};