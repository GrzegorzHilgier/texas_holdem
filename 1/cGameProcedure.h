#pragma once
#include "stdafx.h"
//implements main app alghoritm
//Creates all menus
class cGameProcedure : public cMenu
{	
	cMainMenu* hMenu;
	cMainScreen* hMS;
	cSeatMenu* hSeatMenu;
	cTableMenu* hTableMenu;
	cGameEngine* hGameEngine;
	cBetMenu* hBetMenu;	
	sGameData sGD;
	sInitData sID;
	cDebugger* hDebugger;
	int HumanBet;
	int Timer(int);
	int Scroll(int k) { return 0; }
	int Command(int);
	int init2();

public:

	LPCWSTR nickname[10];
	bool pause;
	HBITMAP h;

	cGameProcedure();

	//Methods used by child menus
	cMainMenu* GethMenu();
	void DeleteChild();
	void StopTimer(int=0);
	void StartTimer(int=0,int=0);
	void GameReset();
	void SeatMenuFinish(int);
	void BetMenuFinish(int);
	sGameData GetGD();
	sInitData GetID();

	~cGameProcedure();
};
