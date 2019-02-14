#pragma once
#include "stdafx.h"
//Big event handler, sends event message to appropiate menu

class WSInterface : public cMenu
{
	cMenu* ScrMask[MAX_SCRIPTS];
	cGameProcedure* hGameProcedure;
	cMainScreen* hMS;
	cMenu* hScript;
	int init2() { return 0; };
public:
	bool pause;
	WSInterface(HINSTANCE hInstt, HWND hWndd);
	~WSInterface();

	//all menus calls below method when created
	int GetIndex(cMenu*);

	//all menus calles below method when destroyed
	void ReleaseScrIndex(int);

	//Event distribution (used by win32 handle script
	void refresh();
	int Command(int CM_Command);
	int Timer(int CM_Command);
	int Scroll(int CM_Command);

	//Required if scroll control operating
	void RegisterScroll(cMenu*);
	//Get acess to important objects
	cMainScreen* GethMS();
	cGameProcedure* GethGP();
};


