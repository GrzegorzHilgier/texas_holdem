#pragma once
#include "stdafx.h"








class WSInterface : public cScript
{
	cScript* ScrMask[MAX_SCRIPTS];
	cGameProcedure* hGameProcedure;
	cMainScreen* hMS;
	cScript* hScript;
public:
	bool pause;
	WSInterface(HINSTANCE hInstt, HWND hWndd);
	~WSInterface();
	


	
	int GetIndex(cScript*);
	void ReleaseScrIndex(int);
	void refresh();
	int Command(int CM_Command);
	int Timer(int);
	int init2() { return 0; };
	int Scroll(int);
	void RegisterScroll(cScript*);
	cMainScreen* GethMS();
	cGameProcedure* GethGP();
};


