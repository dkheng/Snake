#include <windows.h>
#include <iostream>
#include <conio.h>
#include "system.h"
#include "snake.h"
#include "wall.h"
#include "food.h"
#include "rank.h"
#include "menu.h"
#include "buff.h"
#include "sign.h"

extern GridState grids[40][40];
extern int score;
extern int chance;
extern double times;
extern Food f;
extern Sign sign;
extern int crefoodtimes;
extern int rewardflag;
extern double dur;
extern double now;
extern int clag;
int System::mode = 1;

void System::Pos(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//显示或隐藏光标
void System::ShowCursor(bool visible)
{
	//CONSOLE_CURSOR_INFO结构体包含控制台光标信息，成员分别表示光标百分比厚度和是否可见
	CONSOLE_CURSOR_INFO cursor_info = { 20, visible };
	//SetConsoleCursorInfo设定控制台窗口的光标大小和是否可见
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//控制文本颜色
void System::setTextColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void System::signMenu()
{
	system("cls");
	System::ShowCursor(false);
	Pos(54, 14);
	cout << "欢迎来到贪吃蛇小游戏！";
	vector<string> login = { "登录","注册","找回密码","退出游戏" };
	int flag0 = Menu::PrintMenu(login, 4, 61, 18);
	if (flag0 == 1)
	{
		if (sign.userSignIn())
			mainMenu();
		else
		{
			system("cls");
			Pos(0, 0);
			exit(0);
		}
	}
	else if (flag0 == 2)
	{
		if (sign.userSignUp())
		{
			if (sign.userSignIn())
				mainMenu();
			else
			{
				system("cls");
				Pos(0, 0);
				exit(0);
			}
		}
		else
		{
			system("cls");
			Pos(0, 0);
			exit(0);
		}
	}
	else if (flag0 == 3)
	{
		if (sign.forgetPassword())
		{
			if (sign.userSignIn())
				mainMenu();
			else
			{
				system("cls");
				Pos(0, 0);
				exit(0);
			}
		}
		else
		{
			system("cls");
			Pos(0, 0);
			exit(0);
		}
	}
	else
	{
		system("cls");
		Pos(0, 0);
		exit(0);
	}
}

void System::mainMenu()
{
	system("cls");
	Pos(54, 14);
	cout << "欢迎进入贪吃蛇小游戏！";
	vector<string> menu = { "开始游戏","排行榜","游戏说明","退出游戏" };
	int flag = Menu::PrintMenu(menu, 4, 61, 18);
	if (flag == 1)
		modeSelect();
	else if (flag == 2)
		Rank::chooseRank();
	else if (flag == 3)
	{
		system("cls");
		instructions();

	}
	else
	{
		system("cls");
		Pos(0, 0);
		exit(0);
	}
}

void System::newgame()
{
	score = 0;
	Buff::initData();
	rewardflag = 0;
	now = 0;
	crefoodtimes = 0;
	Snake::steps = 0;
	Pos(57, 14);
	cout << "是否开始新的游戏？";
	vector<string> menu = { "YES","NO" };
	int flag = Menu::PrintMenu(menu, 2, 63, 18);
	if (flag == 2) mainMenu();
	system("cls");
	passselect();
}

void System::endgame(GameOverStatus status)
{
	system("color 04");
	Sleep(100);
	system("color 07");
	switch (status)
	{
	case GameOverStatus::wall:
		Pos(96, 22);
		cout << "真不幸，您撞到了墙！";
		break;
	case GameOverStatus::self:
		Pos(96,22);
		cout << "真不幸，您撞到了自己！";
		break;
	case GameOverStatus::bomb:
		Pos(96, 22);
		cout << "真不幸，您炸死了自己！";
		break;
	default:
		Pos(96,22);
		cout << "您已经结束了游戏！";
		break;
	}
	Pos(96, 24);
	cout << "本次游戏总用时为 " << times << " 秒！";
	Pos(96, 26);
	cout << "本次游戏总步数为 " << Snake::steps << " 步！";
	Pos(96, 28);
	cout << "本次游戏总得分为 " << score << " 分！";
	Pos(96, 30);
	cout << "按Enter键继续！";
	while (1)
	{
		Sleep(500);
		if (GetAsyncKeyState(VK_RETURN))
			break;
	}
	dur = 0;
	while (_getch() != '\r');
	system("cls");
	Rank::updateRank();
	newgame();
}

void System::passselect()   //关卡选择界面
{
	system("cls");
	Pos(60, 14);
	cout << "请选择关卡！";
	vector<string> menu = { "第一关","第二关", "第三关", "第四关", "第五关","挑战模式","返回上一级" };
	int flag = Menu::PrintMenu(menu, 7, 62, 18);
	if (flag == 7) modeSelect();
	system("cls");
	Pos(60, 14);
	cout << "请选择速度！";
	vector<string> speed = { "简单","普通","困难","挑战","地狱","返回上一级" };
	int lag = Menu::PrintMenu(speed, 6, 63, 18);
	if (lag == 6) passselect();
	system("cls");
	initGrids();
	if (flag == 1)
	{
		Map1 m;
		m.drawMap();
	}
	else if (flag == 2)
	{
		Map2 m;
		m.drawMap();
	}
	else if (flag == 3)
	{
		Map3 m;
		m.drawMap();
	}
	else if (flag == 4)
	{
		Map4 m;
		m.drawMap();
	}
	else if (flag == 5)
	{
		Map5 m;
		m.drawMap();
	}
	else if (flag == 6)
	{
		Map1 m;
		m.drawMap();
		clag = 1;
	}
	mode = flag;
	Snake snake((6 - lag) * 50);
	System::Pos(96, 2);
	cout << "当前用时：0";
	System::Pos(96, 4);
	cout << "当前步数：" << Snake::steps;
	System::Pos(96, 6);
	cout << "当前速度：" << 50 * (6 - lag);
	System::Pos(96, 8);
	cout << "单个食物分数：" << 2 * lag;
	System::Pos(96, 10);
	cout << "当前得分：" << score;
	System::Pos(96, 12);
	cout << "当前寿命：" << chance;
	snake.show();
	f.create_food();
	snake.move();
}

void System::modeSelect()
{
	system("cls");
	Pos(60, 14);
	cout << "请选择模式！";
	vector<string> menu = { "单人模式","双人竞技模式","返回上一级" };
	int flag = Menu::PrintMenu(menu, 3, 62, 18);
	if (flag == 1) passselect();
	else if (flag == 2) passselect_double();
	else if (flag == 3) mainMenu();
}

void System::newgame_double()
{
	SnakeWASD::scores = 0;
	SnakeDirArrow::scores = 0;
	SnakeWASD::alived = true;
	SnakeDirArrow::alived = true;
	Pos(57, 14);
	cout << "是否开始新的游戏？";
	vector<string> menu = { "YES","NO" };
	int flag = Menu::PrintMenu(menu, 2, 63, 18);
	if (flag == 2) mainMenu();
	system("cls");
	passselect_double();
}

void System::endgame_double(GameOverStatus status)
{
	system("color 04");
	Sleep(100);
	system("color 07");
	switch (status)
	{
	case GameOverStatus::wall:
		Pos(90, 22);
		cout << "双方已全部阵亡！游戏结束！";
		break;
	default:
		Pos(90, 22);
		cout << "您已经结束了游戏！";
		break;
	}
	Pos(90, 24);
	cout << "本次游戏玩家一总得分为 " << SnakeWASD::scores << " 分！";
	Pos(90, 26);
	cout << "本次游戏玩家二总得分为 " << SnakeDirArrow::scores << " 分！";
	Pos(90, 28);
	cout << "按Enter键继续！";
	while (1)
	{
		Sleep(500);
		if (GetAsyncKeyState(VK_RETURN))
			break;
	}
	while (_getch() != '\r');
	system("cls");
	newgame_double();
}

void System::passselect_double()
{
	system("cls");
	Pos(60, 14);
	cout << "请选择关卡！";
	vector<string> menu = { "第一关","第二关", "第三关", "第四关", "第五关","返回上一级" };
	int flag = Menu::PrintMenu(menu, 6, 62, 18);
	if (flag == 6) modeSelect();
	system("cls");
	Pos(60, 14);
	cout << "请选择速度！";
	vector<string> speed = { "简单","普通","困难","挑战","地狱","返回上一级" };
	int lag = Menu::PrintMenu(speed, 6, 63, 18);
	if (lag == 6) passselect_double();
	system("cls");
	initGrids();
	if (flag == 1)
	{
		Map1 m;
		m.drawMap();
	}
	else if (flag == 2)
	{
		Map2 m;
		m.drawMap();
	}
	else if (flag == 3)
	{
		Map3 m;
		m.drawMap();
	}
	else if (flag == 4)
	{
		Map4 m;
		m.drawMap();
	}
	else if (flag == 5)
	{
		Map5 m;
		m.drawMap();
	}
	SnakeWASD snake1((6 - lag) * 50);
	SnakeDirArrow snake2((6 - lag) * 50);
	System::Pos(90, 2);
	cout << "玩家一：蓝蛇，请使用 W A S D 控制。";
	System::Pos(90, 4);
	cout << "玩家二：紫蛇，请使用↑↓← →控制。";
	System::Pos(90, 6);
	cout << "当前速度：" << 50 * (6 - lag);
	System::Pos(90, 8);
	cout << "单个食物分数：" << 2 * lag;
	System::Pos(90, 12);
	cout << "当前玩家一得分：" << snake1.scores;
	System::Pos(90, 14);
	cout << "当前玩家二得分：" << snake1.scores;
	snake1.show();
	snake2.show();
	f.create_food_double();
	while (1)
	{
		Sleep(100);
		if (GetAsyncKeyState(VK_SPACE) & 0x01)
			break;
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
			System::endgame_double(GameOverStatus::esc);
		else if ((GetAsyncKeyState(VK_UP) & 0x01) || (GetAsyncKeyState(0x57) & 0x01) ||
			(GetAsyncKeyState(VK_DOWN) & 0x01) || (GetAsyncKeyState(0x53) & 0x01) ||
			(GetAsyncKeyState(VK_LEFT) & 0x01) || (GetAsyncKeyState(0x41) & 0x01) ||
			(GetAsyncKeyState(VK_RIGHT) & 0x01) || (GetAsyncKeyState(0x44) & 0x01));
	}
	while (1)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x01)
		{
			while (1)
			{
				Sleep(100);
				if (GetAsyncKeyState(VK_SPACE) & 0x01)
					break;
				else if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
					System::endgame_double(GameOverStatus::esc);
				else if ((GetAsyncKeyState(VK_UP) & 0x01) || (GetAsyncKeyState(0x57) & 0x01) ||
					(GetAsyncKeyState(VK_DOWN) & 0x01) || (GetAsyncKeyState(0x53) & 0x01) ||
					(GetAsyncKeyState(VK_LEFT) & 0x01) || (GetAsyncKeyState(0x41) & 0x01) ||
					(GetAsyncKeyState(VK_RIGHT) & 0x01) || (GetAsyncKeyState(0x44) & 0x01));
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
			System::endgame_double(GameOverStatus::esc);
		if (snake1.alived == false && snake2.alived == false)
			System::endgame_double(GameOverStatus::wall);
		if (snake1.alived == true) snake1.move();
		if (snake2.alived == true)snake2.move();
		Sleep((6 - lag) * 50);
	}
}

void System::initGrids()
{
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 40; j++)
			grids[i][j] = GridState::null;
}

int System::randomGenerator(int lower, int upper)
{
	return (rand() % (upper - lower + 1)) + lower;
}

void System::instructions()
{
	int x = 24;
	int y = 14;
	System::Pos(30, y);
	cout << "                         游  戏  说  明";
	System::Pos(x, y + 4);
	cout << "1.可按 ↑ ↓ ← → 或者 W A S D 进行移动。按 + 和 - 改变蛇的速度。";
	System::Pos(x, y + 6);
	cout << "2.蛇撞到墙或者撞到自己会失去一条生命。经过穿梭门后会在相应的穿梭门处出现。";
	System::Pos(x, y + 8);
	cout << "3.难度越大，蛇速度越快，食物分数越高，奖励食物分数也越高。";
	System::Pos(x, y + 10);
	cout << "4.吃掉一定普通食物后会随机出现奖励食物，奖励食物分数随着时间流逝降低，直至消失。";
	System::Pos(x,y + 12);
	cout << "5.获得一定分数后会随机出现 生命 或者 炸弹，一定时间后消失，吃掉它们会获得相应的增益效果。";
	System::Pos(x, y + 14);
	cout << "6.炸弹：向前进方向发射一枚3x3爆炸范围的炸弹，碰到第一个物体后引爆。若为外墙则变为穿梭门，否则消失。";
	System::Pos(x, y + 16);
	cout << "7.生命：当你撞到墙或者自己时失去一条生命，若生命不为零可继续游戏，但炸弹炸到自己会直接死亡。";
	System::Pos(x, y + 18);
	cout << "8.■ 墙体符号  ※ 穿梭符号  ★ 食物符号  ";
	System::setTextColor(0x04);
	cout << "◆";
	System::setTextColor(0x07);
	cout << " 炸弹符号  ";
	System::setTextColor(0x02);
	cout << "◆";
	System::setTextColor(0x07);
	cout<< "生命符号  ";
	System::setTextColor(0x06);
	cout << "★";
	System::setTextColor(0x07);
	cout << " 奖励食物符号";
	System::Pos(x, y + 20);
	system("pause");
	mainMenu();
}