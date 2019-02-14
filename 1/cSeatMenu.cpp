#include"stdafx.h"
int cSeatMenu::init2()
{
	hGP = dynamic_cast<cGameProcedure*>(hParrent);
	//Stop Parrent timer
	hGP->StopTimer();
	//Get gamedata
	GD = hGP->GetGD();
	ID = hGP->GetID();
	//drawing seat choose button

	drawObj(L"BUTTON", L"TAKE A SEAT", x + 80, y + 300, 100, 30);
	if (ID.players == 10)drawObj(L"BUTTON", L"TAKE A SEAT", x + 140, y + 145, 100, 30);
	else drawObj(L"BUTTON", L"TAKE A SEAT", x + 140, y + 145, 100, 30, 0);
	drawObj(L"BUTTON", L"TAKE A SEAT", x + 350, y + 100, 100, 30);
	drawObj(L"BUTTON", L"TAKE A SEAT", x + 610, y + 100, 100, 30);
	if (ID.players == 10)drawObj(L"BUTTON", L"TAKE A SEAT", x + 800, y + 145, 100, 30);
	else drawObj(L"BUTTON", L"TAKE A SEAT", x + 800, y + 145, 100, 30, 0);
	drawObj(L"BUTTON", L"TAKE A SEAT", x + 870, y + 300, 100, 30);
	if (ID.players == 10)drawObj(L"BUTTON", L"TAKE A SEAT", x + 810, y + 450, 100, 30);
	else drawObj(L"BUTTON", L"TAKE A SEAT", x + 810, y + 450, 100, 30, 0);
	drawObj(L"BUTTON", L"TAKE A SEAT", x + 610, y + 510, 100, 30);
	drawObj(L"BUTTON", L"TAKE A SEAT", x + 350, y + 510, 100, 30);
	if (ID.players == 10)drawObj(L"BUTTON", L"TAKE A SEAT", x + 140, y + 450, 100, 30);
	else drawObj(L"BUTTON", L"TAKE A SEAT", x + 140, y + 450, 100, 30, 0);

	return constObj;
}

int cSeatMenu::Command(int x)
{	//sends a chosen seat to hGP
	int result = 0;
	int parameter = x - index;
	hGP->SeatMenuFinish(parameter);
	result = 1;
	return result;
}

cSeatMenu::~cSeatMenu()
{
	for (int i = 0; i < constObj; i++) DestroyWindow(hObj[i]);
	hWSI->ReleaseScrIndex(index);
	hWSI = NULL;
}
