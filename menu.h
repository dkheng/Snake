#pragma once

#include <vector>
#include <string>

using namespace std;

class Menu
{
public:
	static int PrintMenu(vector<string>& menuText, int textNum, int x, int y);
private:
	string content;   //要打印的文本
	int flag;   //节点序号，用于打印函数返回值
	int x, y;   //文本打印开始位置的x，y值
};