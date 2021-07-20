#pragma once

#include <map>
#include <string>
#include "enum.h"

using namespace std;

class Rank
{
public:
	Rank(string n, int s, double t) :nickname(n), hisScores(s), hisTime(t) {}
	static void displayRank(int flag);
	static void updateRank();
	static void chooseRank();
	static map<int, string> filename;
	static map<int, string> roundname;
private:
	string nickname;
	int hisScores;
	double hisTime;
};