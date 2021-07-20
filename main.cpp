#include "snake.h"
#include "system.h"
#include "enum.h"
#include "wall.h"
#include <iostream>
#include "food.h"
#include "sign.h"
using namespace std;

GridState grids[40][40];
int chance = 3;
int score = 0;
double times = 0;
Food f;
Sign sign;
double now = 0;
int crefoodtimes = 0;
int rewardflag = 0;
int clag = 0;
int mapscore = 0;
int porscore = 10;
int portimes = 0;
int main()
{
	system("mode con cols=130 lines=44");
	System::ShowCursor(false);
	srand((unsigned)time(NULL));
	System::signMenu();
	return 0;
}