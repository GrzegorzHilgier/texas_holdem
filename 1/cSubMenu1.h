#pragma once
#include "stdafx.h"
//Gets nick and other game data before game startum
//invokes (hWSI->GethGP())->GameReset();
//TODO: change invoke with delegate or something
class cSubMenu1 : public cMenu
{
	cMainMenu* cMM;
	int init2();
	int Scroll(int k) { return 0; }
	int Command(int);
	int Timer(int);
	
public:
	~cSubMenu1();

};
