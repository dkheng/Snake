#include<iostream>
#include<windows.h>
#include "mouse.h"
Mouse::Mouse() :x(0), y(0)
{
	//�Ƴ����ٱ༭ģʽ(����win10�û�)
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);
}

bool Mouse::leftButtonDown()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x01)
		return true;
	return false;
}

bool Mouse::rightButtonDown()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x01)
		return true;
	return false;
}

bool Mouse::middleButtonDown()
{
	if (GetAsyncKeyState(VK_MBUTTON) & 0x01)
		return true;
	return false;
}

bool Mouse::getCursorWindowPos()
{
	POINT p;   //��p.x��p.y������Ա�����ڴ������λ��
	GetCursorPos(&p);   //��ȡ��������������Ļ��λ��
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ���ڵ�������
	HWND h = GetForegroundWindow();   //��ȡ��㴰�ڵľ��
	ScreenToClient(h, &p);   //ת��Ϊ����ڴ����ϵ�λ��
	x = p.x; y = p.y;
	return true;
}

bool Mouse::getCursorWindowCoor()
{
	if (getCursorWindowPos())
	{
		HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ���ڵ�������
		CONSOLE_FONT_INFO consoleCurrentFont;   //���ڴ��洰��������Ϣ
		GetCurrentConsoleFont(hOutput, FALSE, &consoleCurrentFont); //��ȡ������Ϣ
		x = x / consoleCurrentFont.dwFontSize.X;   //ת��Ϊ����ڴ����ϵ�����
		y = y / consoleCurrentFont.dwFontSize.Y;
		return true;
	}
	return false;
}

bool Mouse::getCursorScreenPos()
{
	POINT p;   //��p.x��p.y������Ա�����ڴ������λ��
	GetCursorPos(&p);   //��ȡ��������������Ļ��λ��
	x = p.x; y = p.y;
	return true;
}