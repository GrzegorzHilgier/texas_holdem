#pragma once
#include "stdafx.h"
class cSubMenu1 : public cMenu
{

	cMainMenu* cMM;
	
public:
	
	
	int init2();
	int Scroll(int k) { return 0; }
	int Command(int );
	int Timer(int);
	~cSubMenu1();


};
