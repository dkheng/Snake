#include<iostream>
#include<fstream>
#include<sstream>
#include<windows.h>
#include "sign.h"
#include "system.h"
#include "menu.h"
using namespace std;

void Sign::inputPassword(string &pass)
{
	pass = "";
	while (1)
	{
		char ch;
		ch = _getch();
		if (ch == 8) //退格键
		{
			if (pass.size()!=0)
			{
				cout << char(8) << " " << char(8);
				pass.pop_back();
			}
		}
		else if (ch == '\r') //回车键
			break;
		else
		{
			cout << "*";
			pass.push_back(ch);
		}
	}
}

int Sign::reSignIn()
{
	system("pause");
	system("cls");
	System::ShowCursor(false);
	vector<string> signin = { "返回上一级","退出" };
	int flag = Menu::PrintMenu(signin, 2, 61, 18);
	if (flag == 1)
	{
		System::signMenu();
		return 1;
	}
	else
		return 0;
}
int Sign::userSignIn()
{
	system("cls");
	if (GetAsyncKeyState(VK_ESCAPE) & 0x0)
		System::signMenu();
	string user_name, pass_word;
	System::ShowCursor(true);
	System::Pos(58, 14);
	cout << "账号：";
	System::Pos(58, 16);
	cout << "密码：";
	System::Pos(64, 14);
	cin >> user_name;
	System::Pos(64, 16);
	//cin >> pass_word;
	inputPassword(pass_word);
	fstream file("user.txt", fstream::in);
	if (!file)
	{
		system("cls");
		System::Pos(56, 16);
		cout << "登陆失败！用户不存在！";
		if (!reSignIn())
			return 0;
	}
	else
	{
		string str;
		while (getline(file, str))
		{
			istringstream in(str);
			in >> account >> password;
			if (account == user_name && password == pass_word)
			{
				system("cls");
				System::Pos(56, 16);
				cout << "登陆成功！";
				system("pause");
				system("cls");
				System::ShowCursor(false);
				System::mainMenu();
				return 1;
			}
		}
		system("cls");
		System::Pos(52, 16);
		cout << "登陆失败，账号或密码输入错误！";
		if (!reSignIn())
			return 0;
		system("cls");
	}
	return 0;
}
int Sign::reSignUp()
{
	system("pause");
	system("cls");
	System::ShowCursor(false);
	vector<string> signin = { "返回上一级","退出" };
	int flag = Menu::PrintMenu(signin, 2, 61, 18);
	if (flag == 1)
	{
		System::signMenu();
		return 1;
	}
	else
		return 0;
}
int Sign::userSignUp()
{
	system("cls");
	string repassword;
	System::ShowCursor(true);
	System::Pos(58, 12); cout << "账号：";
	System::Pos(58, 13); cout << "密码：";
	System::Pos(58, 14); cout << "确认密码：";
	System::Pos(58, 15); cout << "姓名：";
	System::Pos(58, 16); cout << "联系方式：";
	System::Pos(64, 12); cin >> account;
	System::Pos(64, 13); inputPassword(password);
	System::Pos(68, 14); inputPassword(repassword);
	System::Pos(64, 15); cin >> name;
	System::Pos(69, 16); cin >> phoneNumber;
	fstream file("user.txt", fstream::in);
	string str;
	getline(file, str);
	file.close();
	istringstream in(str);
	string ac;
	in >> ac;
	if (ac == account)
	{
		system("cls");
		System::Pos(61, 16);
		cout << "该账号已被注册！";
		if (reSignUp())
			return 0;
	}
	else if (password != repassword)
	{
		system("cls");
		System::Pos(56, 16);
		cout << "两次密码输入不一致";
		if (reSignUp())
			return 0;
	}
	else
	{
		fstream file("user.txt", fstream::app);
		file << account << " " << password << " "
			<< name << " " << phoneNumber<<endl;
		file.close();
		system("cls");
		System::Pos(56, 16);
		cout << "注册成功！";
		system("pause");
		system("cls");
		System::signMenu();
		return 1;
	}
	return 0;
}
int Sign::refindPassword()
{
	system("pause");
	system("cls");
	System::ShowCursor(false);
	vector<string> findback = { "重新找回","退出" };
	int flag = Menu::PrintMenu(findback, 2, 61, 18);
	if (flag == 1)
	{
		forgetPassword();
		return 1;
	}
	else
		return 0;
}
int Sign::forgetPassword()
{
	system("cls");
	System::ShowCursor(true);
	System::Pos(52, 16);
	cout << "请输入要找回密码的账户：";
	System::Pos(52, 18);
	cout << "请输入绑定的手机号：";
	string ac,num;
	System::Pos(76, 16);
	cin >> ac;
	System::Pos(72, 18);
	cin >> num;
	fstream file("user.txt", fstream::in);
	string str;
	while (getline(file, str))
	{
		istringstream in(str);
		in >> account >> password >> name >> phoneNumber;
		if ((ac == account)&&(num == phoneNumber))
		{
			system("cls");
			System::Pos(56, 16);
			in >> account >> password;
			cout << "密码为：" << password;
			System::Pos(56, 17);
			system("pause");
			system("cls");
			System::ShowCursor(false);
			System::signMenu();
			return 1;
		}
	}
	system("cls");
	System::Pos(61, 16);
	cout << "手机号输入错误！";
	if (!refindPassword())
		return 0;
}