#pragma once
#include "stdafx.h"
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
