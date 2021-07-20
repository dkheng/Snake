#include "wall.h"
#include "system.h"
#include <iostream>

using namespace std;

void Wall::initwall()
{
	for (int i = 0; i < 40; i++) { grids[0][i] = GridState::exteriorWall; }
	for (int i = 0; i < 40; i++) { grids[39][i] = GridState::exteriorWall; }
	for (int i = 1; i < 39; i++) { grids[i][0] = GridState::exteriorWall; }
	for (int i = 1; i < 39; i++) { grids[i][39] = GridState::exteriorWall; }
}

void Wall::showMap()
{
	for (int i = 0; i < 40; i++)
	{
		System::Pos(4, i + 2);
		for (int j = 0; j < 40; j++)
		{
			if (grids[i][j] == GridState::wall|| grids[i][j] == GridState::exteriorWall) cout << "¡ö";
			else if (grids[i][j] == GridState::shuttle) cout << "¡ù";
			else cout << "  ";
		}
		cout << endl;
	}
}

void Map1::drawMap() { initwall(); showMap(); }

void Map2::wall_map2()
{
	for (int i = 7; i < 11; i++) { grids[i][0] = grids[i][39] = GridState::shuttle; }
	for (int i = 29; i < 33; i++) { grids[i][0] = grids[i][39] = GridState::shuttle; }
	for (int i = 5; i < 35; i++) { grids[6][i] = grids[28][i] = grids[11][i] = grids[33][i] = GridState::wall; }
}
void Map2::drawMap()
{
	initwall();
	wall_map2();
	showMap();
}

void Map3::wall_map3()
{
	for (int i = 3; i < 17; i++)
	{
		grids[19][i] = grids[20][i] = grids[19][i + 20] = grids[20][i + 20] =
		grids[i][19] = grids[i][20] = grids[i + 20][19] = grids[i + 20][20] = GridState::wall;
	}
	for (int i = 19; i < 21; i++) { grids[0][i] = grids[39][i] = grids[i][0] = grids[i][39] = GridState::shuttle; }
}

void Map3::drawMap()
{
	initwall();
	wall_map3();
	showMap();
}

void Map4::wall_map4()
{
	for (int i = 5; i < 35; i++) { grids[i][5] = grids[5][i] = grids[i][34] = GridState::wall; }
	for (int i = 10; i < 35; i++) { grids[34][i] = grids[i][10] = GridState::wall; }
	for (int i = 10; i < 30; i++) { grids[10][i] = grids[i][29] = GridState::wall; }
	for (int i = 15; i < 30; i++) { grids[29][i] = grids[i][15] = GridState::wall; }
	for (int i = 15; i < 25; i++) { grids[15][i] = grids[i][25] = GridState::wall; }
	for (int i = 20; i < 25; i++) { grids[24][i] = grids[i][20] = GridState::wall; }
	for (int i = 1; i < 5; i++)
	{
		grids[5][i] = grids[i + 34][5] = grids[34][i + 34] = grids[i][34] = GridState::wall;
		grids[i][0] = grids[39][i] = grids[0][i + 34] = grids[i + 34][39] = GridState::shuttle;
		grids[0][i] = grids[i][39] = grids[i + 34][0] = grids[39][i + 34] = GridState::shuttle;
	}
}

void Map4::drawMap()
{
	initwall();
	wall_map4();
	showMap();
}

void Map5::wall_map5()
{
	for (int i = 1; i < 23; i++) { grids[i][5] = grids[5][i + 16] = grids[i + 16][34] = grids[34][i] = GridState::wall; }
	for (int i = 1; i < 18; i++) { grids[i][10] = grids[10][i + 21] = grids[i + 21][29] = grids[29][i] = GridState::wall; }
	for (int i = 10; i < 18; i++) { grids[17][i] = grids[i][22] = grids[22][i + 12] = grids[i + 12][17] = GridState::wall; }
	for (int i = 5; i < 18; i++) { grids[22][i] = grids[i][17] = grids[17][i + 17] = grids[i + 17][22] = GridState::wall; }
	for (int i = 6; i < 10; i++)
	{
		grids[0][i] = grids[39][i] = grids[0][i + 24] = grids[39][i + 24] =
		grids[i][0] = grids[i][39] = grids[i + 24][0] = grids[i + 24][39] = GridState::shuttle;
	}
}
void Map5::drawMap()
{
	initwall();
	wall_map5();
	showMap();
}
