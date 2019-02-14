#pragma once
#include "stdafx.h"
class cSeatMenu : public cMenu
{
	cGameProcedure* hGP;
	sGameData GD;
	sInitData ID;

public:
	int init2();

	int Command(int x);
	int Scroll(int k) { return 0; }
	int Timer(int x) { return 0; }
	~cSeatMenu();

};