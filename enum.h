#pragma once

enum class Direction
{
	up = 0, 
	down = 1, 
	left = 2, 
	right = 3
};

enum class GridState
{
	null = 0,
	food = 1,
	wall = 2,
	snake = 3,
	shuttle = 4,  //穿梭标志
	portal = 5,   //传送门标志
	bomb = 6,
	exteriorWall = 7,
	lifebuff = 8,
	reward = 9,
	snakeWASD = 10,
	snakeDirArrow = 11
};

enum class GameOverStatus
{
	wall = 0,
	self = 1,
	esc = 2,
	bomb = 3
};
