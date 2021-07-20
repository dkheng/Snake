#pragma once
#include<string>
#include<conio.h>
using namespace std;
class Sign {
private:
	string account;
	string password;
	string name;
	string phoneNumber;
public:
	Sign() {}
	void inputPassword(string &pass);
	int userSignIn();
	int userSignUp();
	int reSignIn();
	int reSignUp();
	int refindPassword();
	int forgetPassword();
	string getAccount() { return account; }
};
