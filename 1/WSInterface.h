#pragma once
#include "stdafx.h"
//Big event handler, sends event message to appropiate menu

class WSInterface : public cMenu
{
	cMenu* ScrMask[MAX_SCRIPTS];
	cGameProcedure* hGameProcedure;
	cMainScreen* hMS;
	cMenu* hScript;
public:
	bool pause;
	WSInterface(HINSTANCE hInstt, HWND hWndd);
	~WSInterface();
	int GetIndex(cMenu*);
	void ReleaseScrIndex(int);
	void refresh();
	int Command(int CM_Command);
	int Timer(int);
	int init2() { return 0; };
	int Scroll(int);
	void RegisterScroll(cMenu*);
	cMainScreen* GethMS();
	cGameProcedure* GethGP();
};


