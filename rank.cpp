#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>
#include "rank.h"
#include "system.h"
#include "menu.h"
#include "sign.h"

extern int score;
extern double times;
extern Sign sign;

using namespace std;

map<int, string> Rank::filename = { {1,"map1.txt"},{2,"map2.txt"},
								   {3,"map3.txt"},{4,"map4.txt"},
								   {5,"map5.txt"},{6,"challenge.txt"} };
map<int, string> Rank::roundname = { {1,"第一关排行榜"},{2,"第二关排行榜"},
								   {3,"第三关排行榜"},{4,"第四关排行榜"},
								   {5,"第五关排行榜"},{6,"挑战模式排行榜"} };

void Rank::chooseRank()
{
	system("cls");
	System::Pos(60, 14);
	cout << "请选择关卡！";
	vector<string> menu = { "第一关","第二关","第三关","第四关","第五关","挑战模式","返回主菜单" };
	int flag = Menu::PrintMenu(menu, 7, 62, 18);
	if (flag == 7) System::mainMenu();
	displayRank(flag);
}

void Rank::displayRank(int flag)
{
	system("cls");
	System::Pos(58, 12);
	cout << roundname[flag];
	int x = 46, y = 20, num = 0;
	fstream file(Rank::filename[flag], fstream::in);
	string in_name;
	int in_score;
	double in_time;
	System::Pos(x, 16);
	cout << setw(15) << left << "玩家昵称" << setw(15) << "得分" << "用时";
	System::Pos(x - 2, 18);
	cout << "--------------------------------------";
	while (file >> in_name >> in_score >> in_time)
	{
		num++;
		System::Pos(x, y);
		cout << setw(15) << left <<in_name << setw(15) << in_score << in_time;
		y += 2;
	}
	if (num == 0)
	{
		System::Pos(x, y);
		cout << "该关卡尚无排名！快去创造你的记录吧！";
	}
	file.close();
	System::Pos(56, y + 4);
	system("pause");
	System::mainMenu();
}

void Rank::updateRank()
{
	fstream file(Rank::filename[System::mode], fstream::in);
	list<Rank> rankList;
	string in_name;
	int in_score;
	double in_time;
	while (file >> in_name >> in_score >> in_time)
		rankList.push_back(Rank(in_name, in_score, in_time));
	if (rankList.size() != 0 && score <= rankList.back().hisScores) return;
	System::Pos(53, 16);
	cout << "恭喜您的得分已进入高分榜！";
	System::Pos(53, 18);
	cout << "快去排行榜查看你的辉煌吧！";
	System::Pos(53, 20);
	system("pause");
	auto i = rankList.begin();
	if (rankList.size() > 0)
	{
		for (; i->hisScores > score; i++);
		rankList.insert(i, Rank(sign.getAccount(), score, times));
	}
	else rankList.push_back(Rank(sign.getAccount(), score, times));
	file.close();
	file.open(Rank::filename[System::mode], fstream::out);
	i = rankList.begin();
	for (int j = 0; j < 5 && i != rankList.end(); j++, i++)
		file << i->nickname << " " << i->hisScores << " " << i->hisTime << endl;
	file.close();
	system("cls");
}