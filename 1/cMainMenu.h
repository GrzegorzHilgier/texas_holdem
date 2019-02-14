#pragma once
#include "stdafx.h"
//Controls for game setup
//creates submenu
class cMainMenu : public cMenu
{	
	cMenu* hSubMenu;
	int init2();
	int Command(int x);
	int Timer(int k) { return 0; }
	int Scroll(int k) { return 0; }

public:

	MenuData sMD;
	//Closes submenu, Method called by GameProcedure after game reset
	int reset();
	~cMainMenu();
};