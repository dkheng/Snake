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

//��ʾ�����ع��
void System::ShowCursor(bool visible)
{
	//CONSOLE_CURSOR_INFO�ṹ���������̨�����Ϣ����Ա�ֱ��ʾ���ٷֱȺ�Ⱥ��Ƿ�ɼ�
	CONSOLE_CURSOR_INFO cursor_info = { 20, visible };
	//SetConsoleCursorInfo�趨����̨���ڵĹ���С���Ƿ�ɼ�
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//�����ı���ɫ
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
	cout << "��ӭ����̰����С��Ϸ��";
	vector<string> login = { "��¼","ע��","�һ�����","�˳���Ϸ" };
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
	cout << "��ӭ����̰����С��Ϸ��";
	vector<string> menu = { "��ʼ��Ϸ","���а�","��Ϸ˵��","�˳���Ϸ" };
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
	cout << "�Ƿ�ʼ�µ���Ϸ��";
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
		cout << "�治�ң���ײ����ǽ��";
		break;
	case GameOverStatus::self:
		Pos(96,22);
		cout << "�治�ң���ײ�����Լ���";
		break;
	case GameOverStatus::bomb:
		Pos(96, 22);
		cout << "�治�ң���ը�����Լ���";
		break;
	default:
		Pos(96,22);
		cout << "���Ѿ���������Ϸ��";
		break;
	}
	Pos(96, 24);
	cout << "������Ϸ����ʱΪ " << times << " �룡";
	Pos(96, 26);
	cout << "������Ϸ�ܲ���Ϊ " << Snake::steps << " ����";
	Pos(96, 28);
	cout << "������Ϸ�ܵ÷�Ϊ " << score << " �֣�";
	Pos(96, 30);
	cout << "��Enter��������";
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

void System::passselect()   //�ؿ�ѡ�����
{
	system("cls");
	Pos(60, 14);
	cout << "��ѡ��ؿ���";
	vector<string> menu = { "��һ��","�ڶ���", "������", "���Ĺ�", "�����","��սģʽ","������һ��" };
	int flag = Menu::PrintMenu(menu, 7, 62, 18);
	if (flag == 7) modeSelect();
	system("cls");
	Pos(60, 14);
	cout << "��ѡ���ٶȣ�";
	vector<string> speed = { "��","��ͨ","����","��ս","����","������һ��" };
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
	cout << "��ǰ��ʱ��0";
	System::Pos(96, 4);
	cout << "��ǰ������" << Snake::steps;
	System::Pos(96, 6);
	cout << "��ǰ�ٶȣ�" << 50 * (6 - lag);
	System::Pos(96, 8);
	cout << "����ʳ�������" << 2 * lag;
	System::Pos(96, 10);
	cout << "��ǰ�÷֣�" << score;
	System::Pos(96, 12);
	cout << "��ǰ������" << chance;
	snake.show();
	f.create_food();
	snake.move();
}

void System::modeSelect()
{
	system("cls");
	Pos(60, 14);
	cout << "��ѡ��ģʽ��";
	vector<string> menu = { "����ģʽ","˫�˾���ģʽ","������һ��" };
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
	cout << "�Ƿ�ʼ�µ���Ϸ��";
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
		cout << "˫����ȫ����������Ϸ������";
		break;
	default:
		Pos(90, 22);
		cout << "���Ѿ���������Ϸ��";
		break;
	}
	Pos(90, 24);
	cout << "������Ϸ���һ�ܵ÷�Ϊ " << SnakeWASD::scores << " �֣�";
	Pos(90, 26);
	cout << "������Ϸ��Ҷ��ܵ÷�Ϊ " << SnakeDirArrow::scores << " �֣�";
	Pos(90, 28);
	cout << "��Enter��������";
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
	cout << "��ѡ��ؿ���";
	vector<string> menu = { "��һ��","�ڶ���", "������", "���Ĺ�", "�����","������һ��" };
	int flag = Menu::PrintMenu(menu, 6, 62, 18);
	if (flag == 6) modeSelect();
	system("cls");
	Pos(60, 14);
	cout << "��ѡ���ٶȣ�";
	vector<string> speed = { "��","��ͨ","����","��ս","����","������һ��" };
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
	cout << "���һ�����ߣ���ʹ�� W A S D ���ơ�";
	System::Pos(90, 4);
	cout << "��Ҷ������ߣ���ʹ�á����� �����ơ�";
	System::Pos(90, 6);
	cout << "��ǰ�ٶȣ�" << 50 * (6 - lag);
	System::Pos(90, 8);
	cout << "����ʳ�������" << 2 * lag;
	System::Pos(90, 12);
	cout << "��ǰ���һ�÷֣�" << snake1.scores;
	System::Pos(90, 14);
	cout << "��ǰ��Ҷ��÷֣�" << snake1.scores;
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
	cout << "                         ��  Ϸ  ˵  ��";
	System::Pos(x, y + 4);
	cout << "1.�ɰ� �� �� �� �� ���� W A S D �����ƶ����� + �� - �ı��ߵ��ٶȡ�";
	System::Pos(x, y + 6);
	cout << "2.��ײ��ǽ����ײ���Լ���ʧȥһ�����������������ź������Ӧ�Ĵ����Ŵ����֡�";
	System::Pos(x, y + 8);
	cout << "3.�Ѷ�Խ�����ٶ�Խ�죬ʳ�����Խ�ߣ�����ʳ�����ҲԽ�ߡ�";
	System::Pos(x, y + 10);
	cout << "4.�Ե�һ����ͨʳ����������ֽ���ʳ�����ʳ���������ʱ�����Ž��ͣ�ֱ����ʧ��";
	System::Pos(x,y + 12);
	cout << "5.���һ���������������� ���� ���� ը����һ��ʱ�����ʧ���Ե����ǻ�����Ӧ������Ч����";
	System::Pos(x, y + 14);
	cout << "6.ը������ǰ��������һö3x3��ը��Χ��ը����������һ���������������Ϊ��ǽ���Ϊ�����ţ�������ʧ��";
	System::Pos(x, y + 16);
	cout << "7.����������ײ��ǽ�����Լ�ʱʧȥһ����������������Ϊ��ɼ�����Ϸ����ը��ը���Լ���ֱ��������";
	System::Pos(x, y + 18);
	cout << "8.�� ǽ�����  �� �������  �� ʳ�����  ";
	System::setTextColor(0x04);
	cout << "��";
	System::setTextColor(0x07);
	cout << " ը������  ";
	System::setTextColor(0x02);
	cout << "��";
	System::setTextColor(0x07);
	cout<< "��������  ";
	System::setTextColor(0x06);
	cout << "��";
	System::setTextColor(0x07);
	cout << " ����ʳ�����";
	System::Pos(x, y + 20);
	system("pause");
	mainMenu();
}