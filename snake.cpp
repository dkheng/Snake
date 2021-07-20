#include <iostream>
#include <Windows.h>
#include <ctime>
#include "snake.h"
#include "system.h"
#include "food.h"
#include "buff.h"
#include "wall.h"
#include "sign.h"

using namespace std;

extern GridState grids[40][40];
extern Food f;
extern Sign sign;
extern int score;
extern int chance;
extern double times;
extern int crefoodtimes;
extern int rewardflag;
extern double now;
double dur=0;
extern int clag;
extern int mapscore;
extern int portimes;

clock_t start_t, end_t;
int Snake::steps = 0;
Snake::Snake() :length(5), dir(Direction::right), speed(200),life(chance)
{
	for (int i = 0, x = 56, y = 5; i < 5; i++)
	{
		body.push_back(SnakeBody(x - 2 * i, y));
		grids[y - 2][(x - 2 * i - 4) / 2] = GridState::snake;
	}
}

Snake::Snake(int s, int l, Direction d, int chance, int mode) :length(l), dir(d), speed(s),life(chance)
{
	if (mode == 1)
	{
		for (int i = 0, x = 56, y = 5; i < l; i++)
		{
			body.push_back(SnakeBody(x - 2 * i, y));
			grids[y - 2][(x - 2 * i - 4) / 2] = GridState::snake;
		}
	}
}

void Snake::show()
{
	for (auto i = body.begin(); i != body.end(); i++)
	{
		System::Pos((*i).x, (*i).y);
		cout << (*i).bodyShape;
		grids[i->y - 2][(i->x - 4) / 2] = GridState::snake;
	}
	System::Pos(0, 0);
}

void Snake::move()
{
	while (1)
	{
		Sleep(100);
		if (GetAsyncKeyState(VK_SPACE) & 0x01)
			break;
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
			System::endgame(GameOverStatus::esc);
		else if ((GetAsyncKeyState(VK_UP) & 0x01) || (GetAsyncKeyState(0x57) & 0x01) ||
			(GetAsyncKeyState(VK_DOWN) & 0x01) || (GetAsyncKeyState(0x53) & 0x01) ||
			(GetAsyncKeyState(VK_LEFT) & 0x01) || (GetAsyncKeyState(0x41) & 0x01) ||
			(GetAsyncKeyState(VK_RIGHT) & 0x01) || (GetAsyncKeyState(0x44) & 0x01));
	}
	int timer = speed;
	while (1)
	{
		start_t = clock();
		if (timer >= speed)
		{
			timer = 0;
			//向前移动一格
			if (dir == Direction::up)
				body.push_front(SnakeBody((*body.begin()).x, (*body.begin()).y - 1));
			else if (dir == Direction::down)
				body.push_front(SnakeBody((*body.begin()).x, (*body.begin()).y + 1));
			else if (dir == Direction::left)
				body.push_front(SnakeBody((*body.begin()).x - 2, (*body.begin()).y));
			else if (dir == Direction::right)
				body.push_front(SnakeBody((*body.begin()).x + 2, (*body.begin()).y));
			if (gridCheck() == 1)
			{
				System::Pos((*--body.end()).x, (*--body.end()).y);
				cout << "  ";
				System::Pos(0, 0);
				grids[(*--body.end()).y - 2][((*--body.end()).x - 4) / 2] = GridState::null;
				body.pop_back();
			}
			System::Pos((*body.begin()).x, (*body.begin()).y);
			if(Buff::bombNum>0) System::setTextColor(0x06);
			cout << (*body.begin()).bodyShape;
			if (Buff::bombNum > 0) System::setTextColor(0x07);
			steps++;
			System::Pos(96, 4);
			cout << "执行步数：" << steps;
			System::Pos(0, 0);
			snakeControl();
		}
		if (Buff::bombFire == true)
			Bomb::move();
		Sleep(10);
		timer += 10;
		end_t = clock();
		dur += ((double)end_t - (double)start_t);
		System::Pos(96, 2);
		cout << "当前用时：" << dur / CLOCKS_PER_SEC;
		times = dur / CLOCKS_PER_SEC;
		if (times - now > 10 && now != 0)
		{
			for (int i = 0; i < 40; i++)
			{
				for (int j = 0; j < 40; j++)
				{
					if (grids[i][j] == GridState::reward)
					{
						grids[i][j] = GridState::null;
						System::Pos((j + 2) * 2, i + 2);
						cout << "  ";
						rewardflag = 1;
						crefoodtimes = 0;
						break;
					}
				}
			}
		}
		if (Buff::buffOwn == true && (times - Buff::appearTime) > 10)
		{
			grids[Buff::x][Buff::y] = GridState::null;
			System::Pos((Buff::y + 2) * 2, Buff::x + 2);
			cout << "  ";
			Buff::buffOwn = false;
		}
	}
}
void Snake::knockWall()
{
	System::Pos(96, 12);
	cout << "当前寿命：" <<"   ";
	System::Pos(96, 12);
	cout << "当前寿命：" << life;
	
	end_t = clock();
	dur += ((double)end_t - (double)start_t);
	System::Pos(96, 2);
	cout << "当前用时：" << dur / CLOCKS_PER_SEC;
	times = dur / CLOCKS_PER_SEC;

	while (1)
	{
		Sleep(100);
		if (GetAsyncKeyState(VK_SPACE) & 0x01)
			break;
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
			System::endgame(GameOverStatus::esc);
	}
	start_t = clock();
	for (auto it = ++body.begin(); it != body.end(); it++)
	{
		grids[it->y - 2][(it->x - 4) / 2] = GridState::null;
		System::Pos(it->x, it->y);
		cout << "  ";
	}
	body.pop_front();
	if (body.size() > 2)
	{
		body.pop_front();
		body.pop_front();
	}
	show();
}
void Snake::eatSelf()
{
	System::Pos(96, 12);
	cout << "当前寿命：" << "   ";
	System::Pos(96, 12);
	cout << "当前寿命：" << life;

	end_t = clock();
	dur += ((double)end_t - (double)start_t);
	System::Pos(96, 2);
	cout << "当前用时：" << dur / CLOCKS_PER_SEC;
	times = dur / CLOCKS_PER_SEC;

	while (1)
	{
		Sleep(100);
		if (GetAsyncKeyState(VK_SPACE) & 0x01)
			break;
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
			System::endgame(GameOverStatus::esc);
	}
	start_t = clock();

	for (auto it = ++body.begin(); it != body.end(); it++)
	{
		if ((it->x == (*body.begin()).x) && (it->y == (*body.begin()).y))
		{
			while (it != --body.end())
			{
				grids[(*--body.end()).y - 2][((*--body.end()).x - 4) / 2] = GridState::null;
				System::Pos((*--body.end()).x, (*--body.end()).y);
				cout << "  ";
				body.pop_back();
			}
			break;
		}
	}
}
int Snake::gridCheck()
{
	if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::wall ||
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::exteriorWall)
	{
		if (--life)
		{
			knockWall();
			return 0;
		}
		else
		{
			System::Pos(96, 12);
			cout << "当前寿命：" << "   ";


			System::Pos(96, 12);
			cout << "当前寿命：" << life;
			System::endgame(GameOverStatus::wall);
		}
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::food)
	{
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snake;
		score += (6 - speed / 50) * 2;
		mapscore += (6 - speed / 50) * 2;
		f.create_food();
		System::Pos(96, 10);
		cout << "当前得分：" << score;
		if (score > Buff::threshold) Buff::createBuff();
		return 0;
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::portal)
	{
		System::initGrids();
		mapscore = 0;
		portimes = 0;
		system("cls");
		if (clag == 2) { Map2 m; m.drawMap(); }
		else if (clag == 3) { Map3 m; m.drawMap(); }
		else if (clag == 4) { Map4 m; m.drawMap(); }
		else if (clag == 5) { Map5 m; m.drawMap(); }
		Snake s(speed, 5, Direction::right, life);
		s.show();
		System::Pos(96, 2);
		cout << "当前用时：" << times;
		System::Pos(96, 4);
		cout << "当前步数：" << Snake::steps;
		System::Pos(96, 6);
		cout << "当前速度：" << speed;
		System::Pos(96, 8);
		cout << "单个食物分数：" << 2 * (6 - speed / 50);
		System::Pos(96, 10);
		cout << "当前得分：" << score;
		System::Pos(96, 12);
		cout << "当前寿命：" << life;
		System::Pos(96, 16);
		cout << "你已获得了 " << Buff::bombNum << " 枚炸弹!";
		System::Pos(96, 18);
		cout << "按 F 发射吧！";
		f.create_food();
		s.move();
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::reward)
	{
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snake;
		rewardflag = 1;
		crefoodtimes = 0;
		double get = times;
		score += ((6 - speed / 50) * 2 + 2) * (int)(15 - get + now);
		System::Pos(96, 10);
		cout << "当前得分：" << score;
		if (score > Buff::threshold) Buff::createBuff();
		return 0;
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::snake)
	{
		if (--life)
		{
			eatSelf();
			//return 0;
		}
		else
		{
			System::Pos(96, 12);
			cout << "当前寿命：" << life;
			System::endgame(GameOverStatus::self);
		}
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::shuttle)
	{
		if (dir == Direction::up)
			(*body.begin()).y = 40;
		else if (dir == Direction::down)
			(*body.begin()).y = 3;
		else if (dir == Direction::left)
			(*body.begin()).x = 80;
		else if (dir == Direction::right)
			(*body.begin()).x = 6;
		int flag = gridCheck();
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snake;
		return flag;
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::bomb)
	{
		Buff::bombNum++; Buff::buffOwn = false;
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snake;
		System::Pos(96, 16);
		cout << "你已获得了 " << Buff::bombNum <<" 枚炸弹!";
		System::Pos(96, 18);
		cout << "按 F 发射吧！";
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::lifebuff)
	{
		Buff::buffOwn = false;
		life++;
		System::Pos(96, 12);
		cout << "当前寿命：" << life;
	}
	else
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snake;
	return 1;
}

void Snake::snakeControl()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x01)
	{
		end_t = clock();
		dur += ((double)end_t - (double)start_t);
		System::Pos(96, 2);
		cout << "当前用时：" << dur / CLOCKS_PER_SEC;
		times = dur / CLOCKS_PER_SEC;

		while (1)
		{
			Sleep(100);
			if (GetAsyncKeyState(VK_SPACE) & 0x01)
				break;
			else if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
				System::endgame(GameOverStatus::esc);
			else if ((GetAsyncKeyState(VK_UP) & 0x01) || (GetAsyncKeyState(0x57) & 0x01) ||
				(GetAsyncKeyState(VK_DOWN) & 0x01) || (GetAsyncKeyState(0x53) & 0x01) ||
				(GetAsyncKeyState(VK_LEFT) & 0x01) || (GetAsyncKeyState(0x41) & 0x01) ||
				(GetAsyncKeyState(VK_RIGHT) & 0x01) || (GetAsyncKeyState(0x44) & 0x01));
		}
		start_t = clock();
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
		System::endgame(GameOverStatus::esc);
	else if (((GetAsyncKeyState(VK_UP) & 0x01) && dir != Direction::down) ||
			 ((GetAsyncKeyState(0x57) & 0x01) && dir != Direction::down))
		dir = Direction::up;
	else if (((GetAsyncKeyState(VK_DOWN) & 0x01) && dir != Direction::up) ||
			 ((GetAsyncKeyState(0x53) & 0x01) && dir != Direction::up))
		dir = Direction::down;
	else if (((GetAsyncKeyState(VK_LEFT) & 0x01) && dir != Direction::right) ||
			 ((GetAsyncKeyState(0x41) & 0x01) && dir != Direction::right))
		dir = Direction::left;
	else if (((GetAsyncKeyState(VK_RIGHT) & 0x01) && dir != Direction::left) ||
			 ((GetAsyncKeyState(0x44) & 0x01) && dir != Direction::left))
		dir = Direction::right;
	else if ((GetAsyncKeyState(VK_ADD) & 0x01) && speed >= 100)
	{
		speed -= 50;
		System::Pos(96, 6);
		cout << "当前速度：" << speed << "     ";
		System::Pos(96, 8);
		cout << "单个食物分数：" << (6 - speed / 50) * 2 << "     ";
	}
	else if ((GetAsyncKeyState(VK_SUBTRACT) & 0x01) && speed <= 200)
	{
		speed += 50;
		System::Pos(96, 6);
		cout << "当前速度：" << speed << "     ";
		System::Pos(96, 8);
		cout << "单个食物分数：" << (6 - speed / 50) * 2 << "     ";
	}
	else if ((GetAsyncKeyState(0x46) & 0x01) && Buff::bombNum > 0)
	{
		Buff::bombNum--; Buff::bombFire = true;
		if (Buff::bombNum != 0)
		{
			System::Pos(96, 16);
			cout << "你已获得了 " << Buff::bombNum << " 枚炸弹!";
			System::Pos(96, 18);
			cout << "按 F 发射吧！";
		}
		else
		{
			System::Pos(96, 16);
			cout << "                               ";
			System::Pos(96, 18);
			cout << "                               ";
		}
		if (dir == Direction::up)
			Buff::bombList.push_back(Bomb(body.front().x, body.front().y - 1, dir));
		else if (dir == Direction::down)
			Buff::bombList.push_back(Bomb(body.front().x, body.front().y + 1, dir));
		else if (dir == Direction::left)
			Buff::bombList.push_back(Bomb(body.front().x - 2, body.front().y, dir));
		else if (dir == Direction::right)
			Buff::bombList.push_back(Bomb(body.front().x + 2, body.front().y, dir));
		if (grids[Buff::bombList.back().getY() - 2][(Buff::bombList.back().getX() - 4) / 2] != GridState::null)
		{
			int tempx = body.front().x, tempy = body.front().y;
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
			if (--life)
				knockWall();
			else
			{
				System::Pos(96, 10);
				cout << "当前寿命：" << "   ";


				System::Pos(96, 10);
				cout << "当前寿命：" << life;
				System::endgame(GameOverStatus::wall);
			}
		}
		System::Pos(Buff::bombList.back().getX(), Buff::bombList.back().getY());
		System::setTextColor(0x06);
		cout << "◆";
		System::setTextColor(0x07);
	}
}