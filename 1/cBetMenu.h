#pragma once
#include "stdafx.h"
//Gets bet from player
//ivokes hGP->betMenuFinish()
//TODO implement delegate
class cBetMenu : public cMenu
{
	cGameProcedure* hGP;
	sGameData GD;
	HWND hScrollBar;
	HWND hStatic;
	int pozycja;
	int min, max, cur;
public:
	int init2();
	int Command(int x);
	int Scroll(int wParam);
	int Timer(int x) { return 0; }
	~cBetMenu();
};
