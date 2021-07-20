#pragma once

#include <string>
#include <list>
#include "enum.h"
using namespace std;

class SnakeBody
{
public:
	friend class Snake;
	friend class SnakeWASD;
	friend class SnakeDirArrow;
	SnakeBody(int a, int b) :x(a), y(b) { bodyShape = "¡ñ"; }
private:
	int x, y;
	string bodyShape;
};

class Snake
{
public:
	Snake();
	Snake(int s, int l = 5, Direction d = Direction::right, int chance=3, int mode = 1);
	virtual void show();
	virtual void move();
	void knockWall();
	void eatSelf();
	static int steps;
protected:
	virtual int gridCheck();
	virtual void snakeControl();
	int length;
	Direction dir;
	int speed;
	int life;
	list<SnakeBody> body;
};

class SnakeWASD : public Snake
{
public:
	SnakeWASD(int s, int l = 5, Direction d = Direction::right);
	void move() override;
	void show() override;
	static int scores;
	static bool alived;
private:
	int gridCheck() override;
	void snakeControl() override;
};

class SnakeDirArrow : public Snake
{
public:
	SnakeDirArrow(int s, int l = 5, Direction d = Direction::right);
	void move() override;
	void show() override;
	static int scores;
	static bool alived;
private:
	int gridCheck() override;
	void snakeControl() override;
};