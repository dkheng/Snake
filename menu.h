#pragma once

#include <vector>
#include <string>

using namespace std;

class Menu
{
public:
	static int PrintMenu(vector<string>& menuText, int textNum, int x, int y);
private:
	string content;   //Ҫ��ӡ���ı�
	int flag;   //�ڵ���ţ����ڴ�ӡ��������ֵ
	int x, y;   //�ı���ӡ��ʼλ�õ�x��yֵ
};