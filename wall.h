#pragma once
#include "enum.h"

extern GridState grids[40][40];
class Wall
{
public:
	virtual void drawMap() = 0;
	void initwall();
	void showMap();
};

class Map1 :public Wall
{
public:
	void drawMap();
};

class Map2 :public Wall
{
public:
	void wall_map2();
	void drawMap();
};

class Map3 :public Wall
{
public:
	void wall_map3();
	void drawMap();
};

class Map4 :public Wall
{
public:
	void wall_map4();
	void drawMap();
};

class Map5 :public Wall
{
public:
	void wall_map5();
	void drawMap();
};