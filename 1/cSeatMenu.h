#pragma once
#include "stdafx.h"
//Choosing sitting place by player
//invokes hGP->SeatMenuFinish(parameter);
//TODO: change invoke with delegate or etc
class cSeatMenu : public cMenu
{
	cGameProcedure* hGP;
	sInitData ID;
	int init2();
	int Command(int x);
	int Scroll(int k) { return 0; }
	int Timer(int x) { return 0; }

public:

	~cSeatMenu();

};