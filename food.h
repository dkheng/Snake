#pragma once
#include <string>
#include "system.h"
const int width = 40;
const int height = 40;
extern GridState grids[width][height];
using namespace std;
class Food {
private:
	static int x, y;
	string foodshape;
	string foodreward;
public:
	Food() { foodshape = "бя"; foodreward = "бя"; }
	void create_food();
	void create_food_double();
	static int get_x();
	static int get_y();
	bool Is_Null();
};
