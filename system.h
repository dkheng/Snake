#pragma once

#include "enum.h"
#include <vector>
#include <string>

using namespace std;

class System
{
public:
	static void Pos(int x, int y);
    static void ShowCursor(bool visible);
    static void setTextColor(int color);
    static void signMenu();
    static void mainMenu();
	static void newgame();
	static void endgame(GameOverStatus status);
    static void passselect();
    static void initGrids();
    static int randomGenerator(int lower, int upper);
    static void instructions();
    static int mode;
    static void modeSelect();
    static void passselect_double();
    static void newgame_double();
    static void endgame_double(GameOverStatus status);
};