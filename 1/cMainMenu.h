#pragma once
#include "stdafx.h"
class cMainMenu : public cScript
{
	
	
	cScript* hSubMenu;

public:
	MenuData sMD;
	int init2()
	{
		hSubMenu = NULL;
		drawObj(L"BUTTON", L"New Game", 10, 10, 150, 30);
		drawObj(L"BUTTON", L"Pause", 170, 10, 150, 30);
		return constObj;
	}



	int reset()
	{
		if (hSubMenu)
		{
			delete hSubMenu;
			hSubMenu = NULL;	
		}
		return 0;
	}



	int Command(int x)
	{
		int result = 0;
		/*
		0-New game
		1-Load/save
		*/


		
		
			const int parameter = x - index;

			switch (parameter)


			{
			case 0:
				if (hSubMenu == NULL)
				{
					hSubMenu = new cSubMenu1();
					hSubMenu->init(hInst, hWnd, 0, 0, hWSI,this);
				}
				else { delete hSubMenu; hSubMenu = NULL; }
				break;


			case 1:
				
				
				if (hWSI->pause)hWSI->pause = 0;
				else hWSI->pause = 1;


				
				break;

			default:

				break;


			}

		
		return result;


	}

	int Timer(int k) { return 0; }
	int Scroll(int k) { return 0; }
	~cMainMenu()
	{
		if (hSubMenu) delete hSubMenu;
		hSubMenu = NULL;
		for (int i = 0; i < constObj; i++) DestroyWindow(hObj[i]);
		hWSI->ReleaseScrIndex(index);
		hWSI = NULL;

	}

};