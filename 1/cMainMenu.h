#pragma once
#include "stdafx.h"
class cMainMenu : public cMenu
{	
	cMenu* hSubMenu;
public:
	MenuData sMD;
	int init2();
	int reset();
	int Command(int x);
	int Timer(int k) { return 0; }
	int Scroll(int k) { return 0; }
	~cMainMenu();
};