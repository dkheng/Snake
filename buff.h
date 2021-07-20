#pragma once

#include <map>
#include "enum.h"
#include <string>
#include <vector>

using namespace std;

class Bomb
{
public:
	Bomb(int a, int b, Direction d) :x(a), y(b), dir(d) {  }
	static void move();
	int getX() { return x; }
	int getY() { return y; }
private:
	int x, y;
	Direction dir;
	string shape = "◆";
};

class Buff
{
public:
	static void createBuff();
	static int threshold;
	static int thresholdAdd;
	static int initThreshold;
	static bool buffOwn;
	static double appearTime;
	static int x, y;
	static map<int, GridState> buffList;
	static map<int, string> buffShape;
	//bomb
	static int bombNum;
	static bool bombFire;
	static vector<Bomb> bombList;
	static void initData();

	//lifeBuff
	
};

