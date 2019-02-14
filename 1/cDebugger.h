
#pragma once
#include "stdafx.h"
class cDebugger : public cMenu
{
	cGameProcedure* hGP;
	sGameData GD;
	sInitData ID;
	HWND card1f[10];
	HWND card1c[10];
	HWND card2f[10];
	HWND card2c[10];
	HWND value[10];
	HWND winner[10];
	HWND dealer;
	HWND GS;
	HWND SS;
	HWND actual;
	HWND maxbet;
public:
	int init2();
	void update();
	int Command(int);
	int Scroll(int k) { return 0; }
	int Timer(int);
	~cDebugger();

};