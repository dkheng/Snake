#include "buff.h"
#include "system.h"
#include "food.h"
#include <iostream>
#include <Windows.h>

using namespace std;

extern GridState grids[40][40];
extern Food f;
extern int rewardflag;
extern int crefoodtimes;
extern double times;
int Buff::initThreshold = 200;
int Buff::threshold = initThreshold;
int Buff::thresholdAdd = initThreshold;
bool Buff::buffOwn = false;
double Buff::appearTime = 0;
int Buff::x = 0; int Buff::y = 0;
map<int, GridState> Buff::buffList = { {1,GridState::bomb},{2,GridState::lifebuff} };
map<int, string> Buff::buffShape = { {1,"◆"}, {2,"◆"} };

//bomb
int Buff::bombNum = 0;
bool Buff::bombFire = false;
vector<Bomb> Buff::bombList;

void Buff::createBuff()
{
	if (buffOwn == false)
	{
		do
		{
			x = System::randomGenerator(0, 39);
			y = System::randomGenerator(0, 39);
		} while (!(grids[x][y] == GridState::null));
		int buffFlag = System::randomGenerator(1, 2);
		grids[x][y] = buffList[buffFlag];
		System::Pos((y + 2) * 2, x + 2);
		if (buffFlag == 2) System::setTextColor(0x02);
		else if (buffFlag == 1) System::setTextColor(0x04);
		cout << buffShape[buffFlag];
		System::setTextColor(0x07);
		buffOwn = true;
		appearTime = times;
		threshold += thresholdAdd;
	}
}

void Buff::initData()
{
	threshold = initThreshold;
	buffOwn = false;

	bombNum = 0;
	bombFire = false;
	bombList.clear();
}

void Bomb::move()
{
	for (auto i = Buff::bombList.begin(); i != Buff::bombList.end();)
	{
		int tempx = i->x, tempy = i->y;
		System::Pos(i->x, i->y); cout << "  ";
		if (i->dir == Direction::up) i->y--;
		else if (i->dir == Direction::down) i->y++;
		else if (i->dir == Direction::left) i->x -= 2;
		else if (i->dir == Direction::right) i->x += 2;
		if (grids[i->y - 2][(i->x - 4) / 2] != GridState::null)
		{
			int x[8] = { tempx - 2,tempx,tempx + 2,tempx - 2,tempx + 2,tempx - 2,tempx,tempx + 2 };
			int y[8] = { tempy - 1,tempy - 1,tempy - 1,tempy,tempy,tempy + 1,tempy + 1,tempy + 1 };
			System::setTextColor(0x06);
			System::Pos(tempx, tempy);
			cout << "∷";
			for (int j = 0; j < 8; j++)
			{
				System::Pos(x[j], y[j]);
				cout << "∷";
			}
			System::setTextColor(0x07);
			for (int j = 0; j < 8; j++)
			{
				if (grids[y[j] - 2][(x[j] - 4) / 2] == GridState::snake)
					System::endgame(GameOverStatus::self);
				else if (grids[y[j] - 2][(x[j] - 4) / 2] == GridState::exteriorWall)
					grids[y[j] - 2][(x[j] - 4) / 2] = GridState::shuttle;
				else if (grids[y[j] - 2][(x[j] - 4) / 2] == GridState::food)
				{
					grids[y[j] - 2][(x[j] - 4) / 2] = GridState::null;
					f.create_food();
				}
				else if (grids[y[j] - 2][(x[j] - 4) / 2] == GridState::reward)
				{
					grids[y[j] - 2][(x[j] - 4) / 2] = GridState::null;
					rewardflag = 1;
					crefoodtimes = 0;
				}
				else if (grids[y[j] - 2][(x[j] - 4) / 2] == GridState::shuttle ||
						 grids[y[j] - 2][(x[j] - 4) / 2] == GridState::portal);
				else
					grids[y[j] - 2][(x[j] - 4) / 2] = GridState::null;
			}
			Sleep(100);
			System::Pos(tempx, tempy);
			cout << "  ";
			for (int j = 0; j < 8; j++)
			{
				if (grids[y[j] - 2][(x[j] - 4) / 2] == GridState::shuttle)
				{
					System::Pos(x[j], y[j]);
					cout << "※";
					if (y[j] - 2 == 0)
					{
						System::Pos(x[j], y[j] + 39);
						cout << "※";
						grids[y[j] + 37][(x[j] - 4) / 2] = GridState::shuttle;
					}
					else if (y[j] - 41 == 0)
					{
						System::Pos(x[j], y[j] - 39);
						cout << "※";
						grids[y[j] - 41][(x[j] - 4) / 2] = GridState::shuttle;
					}
					else if (x[j] - 4 == 0)
					{
						System::Pos(x[j]+78, y[j]);
						cout << "※";
						grids[y[j] - 2][(x[j] + 74) / 2] = GridState::shuttle;
					}
					else if (x[j] - 82 == 0)
					{
						System::Pos(x[j] - 78, y[j]);
						cout << "※";
						grids[y[j] - 2][(x[j] - 82) / 2] = GridState::shuttle;
					}
				}
				else
				{
					System::Pos(x[j], y[j]);
					cout << "  ";
				}
			}
			i = Buff::bombList.erase(i);
		}
		else
		{
			System::setTextColor(0x06);
			System::Pos(i->x, i->y); cout << "◆";
			System::setTextColor(0x07);
			i++;
		}
	}
	if (Buff::bombList.size() == 0) Buff::bombFire = false;
}