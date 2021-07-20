#include <iostream>
#include <Windows.h>
#include <ctime>
#include "snake.h"
#include "system.h"
#include "food.h"

extern Food f;

int SnakeWASD::scores = 0;
bool SnakeWASD::alived = true;
int SnakeDirArrow::scores = 0;
bool SnakeDirArrow::alived = true;

SnakeWASD::SnakeWASD(int s, int l, Direction d) :Snake(s,l,d,1,0)
{
	for (int i = 0, x = 56, y = 5; i < l; i++)
	{
		body.push_back(SnakeBody(x - 2 * i, y));
		grids[y - 2][(x - 2 * i - 4) / 2] = GridState::snakeWASD;
	}
}

void SnakeWASD::move()
{
	//向前移动一格
	if (dir == Direction::up)
		body.push_front(SnakeBody((*body.begin()).x, (*body.begin()).y - 1));
	else if (dir == Direction::down)
		body.push_front(SnakeBody((*body.begin()).x, (*body.begin()).y + 1));
	else if (dir == Direction::left)
		body.push_front(SnakeBody((*body.begin()).x - 2, (*body.begin()).y));
	else if (dir == Direction::right)
		body.push_front(SnakeBody((*body.begin()).x + 2, (*body.begin()).y));
	int flag = gridCheck();
	if ( flag == 1)
	{
		System::Pos((*--body.end()).x, (*--body.end()).y);
		cout << "  ";
		System::Pos(0, 0);
		grids[(*--body.end()).y - 2][((*--body.end()).x - 4) / 2] = GridState::null;
		body.pop_back();
	}
	if (flag != 2)
	{
		System::setTextColor(0x01);
		System::Pos((*body.begin()).x, (*body.begin()).y);
		cout << (*body.begin()).bodyShape;
		System::setTextColor(0x07);
	}
	snakeControl();
}

void SnakeWASD::show()
{
	System::setTextColor(0x01);
	for (auto i = body.begin(); i != body.end(); i++)
	{
		System::Pos((*i).x, (*i).y);
		cout << (*i).bodyShape;
		grids[i->y - 2][(i->x - 4) / 2] = GridState::snake;
	}
	System::setTextColor(0x07);
}

int SnakeWASD::gridCheck()
{
	if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::wall ||
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::exteriorWall)
	{
		alived = false;
		System::Pos(90, 22);
		cout << "玩家一已阵亡！";
		System::Pos(90, 24);
		cout << "本次游戏玩家一总得分为 " << scores << " 分！";
		return 2;
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::food)
	{
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snakeWASD;
		f.create_food_double();
		scores += (6 - speed / 50) * 2;
		System::Pos(90, 12);
		cout << "当前玩家一得分：" << scores;
		return 0;
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::snakeWASD)
	{
		alived = false;
		System::Pos(90, 22);
		cout << "玩家一已阵亡！";
		System::Pos(90, 24);
		cout << "本次游戏玩家一总得分为 " << scores << " 分！";
		return 2;
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::snakeDirArrow)
	{
		alived = false;
		SnakeDirArrow::alived = false;
		return 2;
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
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snakeWASD;
		return flag;
	}
	else
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snakeWASD;
	return 1;
}

void SnakeWASD::snakeControl()
{
	if ((GetAsyncKeyState(0x57) & 0x01) && dir != Direction::down)
		dir = Direction::up;
	else if ((GetAsyncKeyState(0x53) & 0x01) && dir != Direction::up)
		dir = Direction::down;
	else if ((GetAsyncKeyState(0x41) & 0x01) && dir != Direction::right)
		dir = Direction::left;
	else if ((GetAsyncKeyState(0x44) & 0x01) && dir != Direction::left)
		dir = Direction::right;
}

SnakeDirArrow::SnakeDirArrow(int s, int l, Direction d) :Snake(s, l, d, 1, 0)
{
	for (int i = 0, x = 36, y = 33; i < l; i++)
	{
		body.push_back(SnakeBody(x - 2 * i, y));
		grids[y - 2][(x - 2 * i - 4) / 2] = GridState::snakeDirArrow;
	}
}

void SnakeDirArrow::move()
{
	//向前移动一格
	if (dir == Direction::up)
		body.push_front(SnakeBody((*body.begin()).x, (*body.begin()).y - 1));
	else if (dir == Direction::down)
		body.push_front(SnakeBody((*body.begin()).x, (*body.begin()).y + 1));
	else if (dir == Direction::left)
		body.push_front(SnakeBody((*body.begin()).x - 2, (*body.begin()).y));
	else if (dir == Direction::right)
		body.push_front(SnakeBody((*body.begin()).x + 2, (*body.begin()).y));
	int flag = gridCheck();
	if (flag == 1)
	{
		System::Pos((*--body.end()).x, (*--body.end()).y);
		cout << "  ";
		grids[(*--body.end()).y - 2][((*--body.end()).x - 4) / 2] = GridState::null;
		body.pop_back();
	}
	if (flag != 2)
	{
		System::setTextColor(0x05);
		System::Pos((*body.begin()).x, (*body.begin()).y);
		cout << (*body.begin()).bodyShape;
		System::setTextColor(0x07);
	}
	snakeControl();
}

void SnakeDirArrow::show()
{
	System::setTextColor(0x05);
	for (auto i = body.begin(); i != body.end(); i++)
	{
		System::Pos((*i).x, (*i).y);
		cout << (*i).bodyShape;
		grids[i->y - 2][(i->x - 4) / 2] = GridState::snake;
	}
	System::setTextColor(0x07);
}

int SnakeDirArrow::gridCheck()
{
	if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::wall ||
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::exteriorWall)
	{
		alived = false;
		System::Pos(90, 22);
		cout << "玩家二已阵亡！";
		System::Pos(90, 24);
		cout << "本次游戏玩家二总得分为 " << scores << " 分！";
		return 2;
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::food)
	{
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snakeDirArrow;
		f.create_food_double();
		scores += (6 - speed / 50) * 2;
		System::Pos(90, 14);
		cout << "当前玩家二得分：" << scores;
		return 0;
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::snakeWASD)
	{
		alived = false;
		SnakeWASD::alived = false;
		return 2;
	}
	else if (grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] == GridState::snakeDirArrow)
	{
		alived = false;
		System::Pos(90, 22);
		cout << "玩家二已阵亡！";
		System::Pos(90, 24);
		cout << "本次游戏玩家二总得分为 " << scores << " 分！";
		return 2;
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
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snakeDirArrow;
		return flag;
	}
	else
		grids[(*body.begin()).y - 2][((*body.begin()).x - 4) / 2] = GridState::snakeDirArrow;
	return 1;
}

void SnakeDirArrow::snakeControl()
{
	if ((GetAsyncKeyState(VK_UP) & 0x01) && dir != Direction::down)
		dir = Direction::up;
	else if ((GetAsyncKeyState(VK_DOWN) & 0x01) && dir != Direction::up)
		dir = Direction::down;
	else if ((GetAsyncKeyState(VK_LEFT) & 0x01) && dir != Direction::right)
		dir = Direction::left;
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x01) && dir != Direction::left)
		dir = Direction::right;
}