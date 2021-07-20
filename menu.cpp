#include "menu.h"
#include "system.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "mouse.h"

//menuTextΪ��ά���飬�洢Ҫ��ӡ�Ĳ˵������б�
//textNumΪ�˵���Ŀ����menuText��һά�Ĵ�С
//x��y�ֱ�Ϊ�˵������Ͻǵĺ�������
//���ر�ѡ��Ĳ˵����
//ʹ��ʾ����
//char menu[4][50]={"1.��¼","2.ע��","3.�������룿","4.�˳�ϵͳ"};
//PrintMenu(menu,4,2,1);
int Menu::PrintMenu(vector<string>& menuText, int textNum, int x, int y)
{
	ShowCursor(false);
	vector<Menu> menu(textNum);
	for (int i = 0; i < textNum; i++)
	{
		menu[i].content = menuText[i];
		menu[i].flag = i + 1;
		menu[i].x = x;
		menu[i].y = y + 2 * i;
	}
	auto nowmenu = menu.begin();
	for (; nowmenu != menu.end(); nowmenu++)
	{
		System::Pos((*nowmenu).x, (*nowmenu).y);
		cout << (*nowmenu).content;
	}
	nowmenu = menu.begin();
	System::setTextColor(0xB0);
	System::Pos((*nowmenu).x - 2, (*nowmenu).y);
	cout << "  " << (*nowmenu).content << "  ";
	System::setTextColor(0x07);

	Mouse m;
	while (GetAsyncKeyState(VK_RETURN) ||
		GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_UP));
	while (1)
	{
		m.getCursorWindowCoor();
		for (auto i = menu.begin(); i != menu.end(); i++)
		{
			if ((m.getY() == i->y) && (m.getX() > i->x)
				&& (m.getX() < (int)(i->x + i->content.size()))
				&& nowmenu != i)
			{
				System::Pos((*nowmenu).x - 2, (*nowmenu).y);
				cout << "  " << (*nowmenu).content << "  ";
				nowmenu = i;
				System::setTextColor(0xB0);
				System::Pos((*nowmenu).x - 2, (*nowmenu).y);
				cout << "  " << (*nowmenu).content << "  ";
				System::setTextColor(0x07);
				break;
			}
		}
		if (GetAsyncKeyState(VK_UP) & 0x01)
		{
			System::Pos((*nowmenu).x - 2, (*nowmenu).y);
			cout << "  " << (*nowmenu).content << "  ";
			if (nowmenu != menu.begin())
				nowmenu--;
			else
				nowmenu = --menu.end();
			System::setTextColor(0xB0);
			System::Pos((*nowmenu).x - 2, (*nowmenu).y);
			cout << "  " << (*nowmenu).content << "  ";
			System::setTextColor(0x07);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x01)
		{
			System::Pos((*nowmenu).x - 2, (*nowmenu).y);
			cout << "  " << (*nowmenu).content << "  ";
			if (nowmenu != --menu.end())
				nowmenu++;
			else
				nowmenu = menu.begin();
			System::setTextColor(0xB0);
			System::Pos((*nowmenu).x - 2, (*nowmenu).y);
			cout << "  " << (*nowmenu).content << "  ";
			System::setTextColor(0x07);
		}
		else if ((GetAsyncKeyState(VK_RETURN) & 0x01))
		{
			System::setTextColor(0x10);
			System::Pos((*nowmenu).x - 2, (*nowmenu).y);
			cout << "  " << (*nowmenu).content << "  ";
			System::setTextColor(0x07);
			Sleep(30);
			while (_getch() != '\r');
			return (*nowmenu).flag;
		}
		else if ((m.leftButtonDown() || m.rightButtonDown())
			&& (m.getY() == nowmenu->y) && (m.getX() > nowmenu->x)
			&& (m.getX() < (int)(nowmenu->x + nowmenu->content.size())))
		{
			System::setTextColor(0x10);
			System::Pos((*nowmenu).x - 2, (*nowmenu).y);
			cout << "  " << (*nowmenu).content << "  ";
			System::setTextColor(0x07);
			Sleep(30);
			return (*nowmenu).flag;
		}
		else if ((GetAsyncKeyState(VK_SPACE) & 0x01) ||
			(GetAsyncKeyState(VK_LEFT) & 0x01) || (GetAsyncKeyState(VK_RIGHT) & 0x01));
	}
}

