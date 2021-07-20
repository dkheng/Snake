#include<iostream>
#include<windows.h>
#include "mouse.h"
Mouse::Mouse() :x(0), y(0)
{
	//移除快速编辑模式(对于win10用户)
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
	POINT p;   //有p.x和p.y两个成员，用于储存鼠标位置
	GetCursorPos(&p);   //获取鼠标相对于整个屏幕的位置
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);   //获取窗口的输出句柄
	HWND h = GetForegroundWindow();   //获取最顶层窗口的句柄
	ScreenToClient(h, &p);   //转换为鼠标在窗口上的位置
	x = p.x; y = p.y;
	return true;
}

bool Mouse::getCursorWindowCoor()
{
	if (getCursorWindowPos())
	{
		HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);   //获取窗口的输出句柄
		CONSOLE_FONT_INFO consoleCurrentFont;   //用于储存窗口字体信息
		GetCurrentConsoleFont(hOutput, FALSE, &consoleCurrentFont); //获取字体信息
		x = x / consoleCurrentFont.dwFontSize.X;   //转换为鼠标在窗口上的坐标
		y = y / consoleCurrentFont.dwFontSize.Y;
		return true;
	}
	return false;
}

bool Mouse::getCursorScreenPos()
{
	POINT p;   //有p.x和p.y两个成员，用于储存鼠标位置
	GetCursorPos(&p);   //获取鼠标相对于整个屏幕的位置
	x = p.x; y = p.y;
	return true;
}