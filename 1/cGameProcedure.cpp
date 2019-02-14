
#include "stdafx.h"

cGameProcedure::cGameProcedure(){}

int cGameProcedure::init2()
{
	//main screen handle and setup
	
	hMS = hWSI->GethMS();
	h = (HBITMAP)LoadImage(hInst, L"Resources/main.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (h)hMS->update(h);
	DeleteObject(h);
	h = NULL;
	
	//menu setup
	hMenu = new cMainMenu;
	hMenu->init(hInst, hWnd, 0, 0, hWSI, this);
	
	//handle setup
	hSeatMenu = NULL;
	hTableMenu = NULL;
	hBetMenu = NULL;
	hDebugger = NULL;
	

	HumanBet = 0;
	return 0;
}
void cGameProcedure::DeleteChild()
{
	if (hSeatMenu)
	{
		delete hSeatMenu;
		hSeatMenu = NULL;
	}
	if (hTableMenu)
	{
		delete hTableMenu;
		hTableMenu = NULL;
	}
	if (hGameEngine)
	{
		delete hGameEngine;
		hGameEngine = NULL;
	}
	if (hDebugger)
	{
		delete hDebugger;
		hDebugger = NULL;
	}
	if (hBetMenu)
	{
		delete hBetMenu;
		hBetMenu = NULL;
	}


}
void cGameProcedure::GameReset()
{	
	//Deleting old game
	DeleteChild();

	//Hide submenu
	hMenu->reset();
	//Bitmap update
	if(h)DeleteObject(h);
	h = (HBITMAP)LoadImage(hInst, L"Resources/table.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (h)hMS->update(h);

	//Game init data structure setup
	sID.players = hMenu->sMD.players;
	sID.stack = hMenu->sMD.stack;


	

	for (int i = 0; i < 10; i++)
	{

		nickname[i] = L"BOT";
	}
	

	//SeatMenu setup
	hSeatMenu = new cSeatMenu;
	hSeatMenu->init(hInst, hWnd, -3, 18, hWSI, this);


}
void cGameProcedure::BetMenuFinish(int bet)
{
	HumanBet = bet;
	delete hBetMenu;
	hBetMenu = NULL;
	StartTimer(50);
}
void cGameProcedure::SeatMenuFinish(int k)
{
	//Game data setup
	nickname[k] = hMenu->sMD.nickname;
	for (int i = 0; i < 10; i++)sID.human[i] = 0;
	sID.human[k] = 1;
	sID.blind = 2;
	//SeatMenu delete
	delete hSeatMenu;
	hSeatMenu = NULL;
	//Game start
	for (int i = 0; i < 10; i++)
		sGD.player[i].card1 = { 0,0 };
	
	hGameEngine = new cGameEngine(sID, &sGD);
	//////////////////DEBUG/////////////////
	//hDebugger = new cDebugger;
	//hDebugger->init(hInst, hWnd, 0, 15, hWSI, this);
	////////////////////////////////////////
	StartTimer();
	
	//New table menu
	hTableMenu = new cTableMenu;
	hTableMenu->init(hInst, hWnd, 0, 0, hWSI, this);



}
int cGameProcedure::Command(int x)
{
	return 0;
}

int cGameProcedure::Timer(int x)


{
	if (!hWSI->pause)
	{

		hGameEngine->Trigger(HumanBet);
		//hDebugger->update();
		hTableMenu->Update();

		if (HumanBet)HumanBet = 0;

		switch (sGD.eGS)
		{
		case GS_HUMAN:
		{
			hBetMenu = new cBetMenu();
			hBetMenu->init(hInst, hWnd, 700, 600, hWSI, this);
			
			break;
		}
		case GS_ENDGAME:
		{
			
			StopTimer();
			MessageBox(hWnd, L"FINISH", towstr(sGD.winner).c_str(), NULL);
			
			break;
		}

		default:

			break;
		}
	}
	return 0;
}


void cGameProcedure::StopTimer(int x)
{
	int ind;
	if (x == 0)ind = index;
	else ind = x;


	KillTimer(hWnd, ind);

}
void cGameProcedure::StartTimer(int time , int x )
{
	int ind;
	if (x == 0)ind = index;
	else ind = x;
	int t = 1000;
	if (time != 0)t = time;
	
	if (SetTimer(hWnd, ind, t, NULL) == 0)MessageBox(hWnd, L"timer error", L"", NULL);

	
}


sGameData cGameProcedure::GetGD()
{
	return sGD;

}
sInitData cGameProcedure::GetID()
{
	return sID;

}
cMainMenu* cGameProcedure::GethMenu()
{
	return hMenu;
}
cGameProcedure::~cGameProcedure()
{
	DeleteObject(h);
	hWSI->ReleaseScrIndex(index);
	KillTimer(hWnd, index);
	DeleteChild();
	if (hMenu)delete hMenu;

	
	hMenu = NULL;
	

}