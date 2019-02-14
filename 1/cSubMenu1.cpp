#include "stdafx.h"

int cSubMenu1::init2()
{

	cMM = dynamic_cast<cMainMenu*>(hParrent);
	
	cMM->sMD.players = 10;
	cMM->sMD.stack = 1500;


	drawObj(L"BUTTON", L"-", 10, 60, 30, 20);
	drawObj(L"BUTTON", L"+", 100, 60, 30, 20);
	drawObj(L"BUTTON", L"-", 10, 100, 30, 20);
	drawObj(L"BUTTON", L"+", 100, 100, 30, 20);
	drawObj(L"BUTTON", L"BEGIN", 10, 180, 220, 30);

	drawObj(L"STATIC", towstr(cMM->sMD.players).c_str(), 50, 60, 40, 20);
	drawObj(L"STATIC", L"PLAYERS", 140, 60, 90, 20);
	drawObj(L"STATIC", towstr(cMM->sMD.stack).c_str(), 50, 100, 40, 20);
	drawObj(L"STATIC", L"STACK", 140, 100, 90, 20);
	drawObj(L"EDIT", NULL, 10, 140, 120, 20);
	drawObj(L"STATIC", L"NICKNAME", 140, 140, 90, 20);
	return constObj;
}

int cSubMenu1::Command(int x)
{
	int result = 0;


	const int parameter = x - index;

	switch (parameter)

	{
	case 0:
		cMM->sMD.players = 6;
		SetWindowText(hObj[5], towstr(cMM->sMD.players).c_str());
		break;

	case 1:
		cMM->sMD.players = 10;
		SetWindowText(hObj[5], towstr(cMM->sMD.players).c_str());
		break;

	case 2:
		if (cMM->sMD.stack > 500)
		{
			cMM->sMD.stack -= 100;
			SetWindowText(hObj[7], towstr(cMM->sMD.stack).c_str());
		}
		break;
	case 3:
		if (cMM->sMD.stack < 2500)
		{
			cMM->sMD.stack += 100;
			SetWindowText(hObj[7], towstr(cMM->sMD.stack).c_str());
		}
		break;
	case 4:


		GetWindowText(hObj[9], cMM->sMD.nickname, MAX_NICKNAME - 1);
		result = 1;
		(hWSI->GethGP())->GameReset();
		
		break;
	default:
		break;

	}



	return(result);
}
int cSubMenu1::Timer(int k) { return 0; }
cSubMenu1::~cSubMenu1()
{
	for (int i = 0; i < constObj; i++) DestroyWindow(hObj[i]);

	hWSI->ReleaseScrIndex(index);
	hWSI = NULL;

}
