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
	
public:
	LPCWSTR nickname[10];
	bool pause;
	HBITMAP h;
	cGameProcedure();
	cMainMenu* GethMenu();
	int init2();
	void DeleteChild();
	void StopTimer(int=0);
	void StartTimer(int=0,int=0);
	int Command(int);
	void GameReset();
	void SeatMenuFinish(int);
	void BetMenuFinish(int);
	int Timer(int);
	int Scroll(int k) { return 0; }
	sGameData GetGD();
	sInitData GetID();
	~cGameProcedure();
};
