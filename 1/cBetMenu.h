#pragma once
#include "stdafx.h"
class cBetMenu : public cScript
{
	cGameProcedure* hGP;
	sGameData GD;
	HWND hScrollBar;
	HWND hStatic;
	
	int pozycja;
	int min, max, cur;

public:
	int init2()
	{
		hGP = dynamic_cast<cGameProcedure*>(hParrent);
		//Stop Parrent timer
		//hGP->StopTimer();
		//Get gamedata
		hGP->StopTimer();
		GD = hGP->GetGD();

		//drawing bet buttons
		if(GD.maxbet==0&&GD.player[GD.actual].raise==0)
		drawObj(L"BUTTON", L"CHECK", 0 , 40, 100, 30);
		else
		drawObj(L"BUTTON", L"FOLD", 0, 40, 100, 30);
		if (GD.player[GD.actual].stack+ GD.player[GD.actual].bet >= GD.maxbet+GD.blind)
		{
			hWSI->RegisterScroll(this);
			pozycja=min =cur= GD.maxbet-GD.player[GD.actual].bet;
			max = GD.player[GD.actual].stack;
			drawObj(L"BUTTON", L"BET",110, 40, 100, 30);
			hScrollBar= drawObj(L"SCROLLBAR", NULL, 0, 10 , 150, 20);
			hStatic=drawObj(L"STATIC", towstr(min).c_str(), 160, 10,50, 20);

			SCROLLINFO si;
			ZeroMemory(&si, sizeof(si));

			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE | SIF_POS;
			si.nMin = min;
			si.nMax = max;			
			si.nPos = min;
			SetScrollInfo(hScrollBar, SB_CTL, &si, TRUE);
		}
		else
		{
			drawObj(L"BUTTON", L"ALL-IN!", 110, 40, 100, 30);
			pozycja = GD.player[GD.actual].stack;
		}

		return constObj;
	}

	int Command(int x)
	{	
		int param = x - index;
		switch (param)
		{
		case 0:
			pozycja = 0;
			hGP->BetMenuFinish(pozycja);
			break;
		case 1:
			
			hGP->BetMenuFinish(pozycja);
			
			break;


		}
		
		return 0;
	}
	int Scroll(int wParam) 
	{

		SCROLLINFO si;
		ZeroMemory(&si, sizeof(si));
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS | SIF_PAGE | SIF_TRACKPOS;
		GetScrollInfo(hScrollBar, SB_CTL, &si);

		 pozycja = si.nPos;

		switch (LOWORD(wParam)) {
		case SB_LEFT:
			pozycja = min;
			break;
		case SB_RIGHT:
			pozycja = max;
			break;
		case SB_LINELEFT:
			if (pozycja > min) {
				pozycja = pozycja - GD.blind;
			}
			break;
		case SB_LINERIGHT:
			if (pozycja < max) {
				pozycja=pozycja+ GD.blind;
			}
			break;
		case SB_PAGELEFT:
			pozycja -= si.nPage;
			if (pozycja < min) {
				pozycja = min;
			}
			break;
		case SB_PAGERIGHT:
			pozycja += si.nPage;
			if (pozycja > max) {
				pozycja = max;
			}
			break;
		case SB_THUMBPOSITION:
			pozycja = ((si.nTrackPos/GD.blind)*GD.blind);
			break;
		case SB_THUMBTRACK:
			pozycja = ((si.nTrackPos / GD.blind)*GD.blind);
			break;
		}

		ZeroMemory(&si, sizeof(si));
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		si.nPos = pozycja;

		SetWindowText(hStatic, towstr(pozycja).c_str());
		SetScrollInfo(hScrollBar, SB_CTL, &si, TRUE);
		return 0;

	}

		
		
		
	
	int Timer(int x) { return 0; }
	~cBetMenu()
	{
		for (int i = 0; i < constObj; i++) DestroyWindow(hObj[i]);
		hWSI->ReleaseScrIndex(index);
		hWSI = NULL;

	}

};
