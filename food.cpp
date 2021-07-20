#include<iostream>
#include<ctime>
#include "system.h"
#include "food.h"
int Food::x = 0;
int Food::y = 0;
extern double times;
extern double now;
extern int crefoodtimes;
extern int rewardflag;
extern int clag;
extern int score;
extern int mapscore;
extern int porscore;
extern int portimes;

bool Food::Is_Null()
{
	if (grids[y-2][(x-4)/2] == GridState::null)
		return true;
	else
		return false;
}
void Food::create_food()
{
	srand((unsigned)time(NULL));
	do
	{
		x = rand() % (76) + 6;
		y = rand() % (37) + 3;
	} while ((!Is_Null()) || (x % 2));
	System::Pos(x, y);
	cout << foodshape;
	grids[y - 2][(x - 4) / 2] = GridState::food;
	if (crefoodtimes % 5 == 0 && crefoodtimes >= 5 && rewardflag <= 1)
	{
		do
		{
			x = rand() % (76) + 6;
			y = rand() % (37) + 3;
		} while ((!Is_Null()) || (x % 2));
		System::Pos(x, y);
		System::setTextColor(0x06);
		cout << foodreward;
		System::setTextColor(0x07);
		grids[y - 2][(x - 4) / 2] = GridState::reward;
		now = times;
		rewardflag = 2;
	}
	if (clag > 0 && clag < 5 && mapscore >= porscore && portimes != 1)
	{
		do
		{
			x = rand() % (76) + 6;
			y = rand() % (37) + 3;
		} while ((!Is_Null()) || (x % 2));
		System::Pos(x, y);
		cout << "LH";
		grids[y - 2][(x - 4) / 2] = GridState::portal;
		clag++;
		portimes = 1;
	}
	crefoodtimes++;
}

void Food::create_food_double()
{
	srand((unsigned)time(NULL));
	do
	{
		x = rand() % (76) + 6;
		y = rand() % (37) + 3;
	} while ((!Is_Null()) || (x % 2));
	System::Pos(x, y);
	cout << foodshape;
	grids[y - 2][(x - 4) / 2] = GridState::food;
}
int Food::get_x()
{
	return x;
}
int Food::get_y()
{
	return y;
}