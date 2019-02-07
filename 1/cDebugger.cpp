#include "stdafx.h"


int cDebugger::init2()
{
	hGP = dynamic_cast<cGameProcedure*>(hParrent);
	//Stop Parrent timer

	//Get gamedata
	GD = hGP->GetGD();
	ID = hGP->GetID();

	int w = 25;
	int h = 20;

	drawObj(L"STATIC", L"UKLAD", 10  , 590, w*2, h);
	drawObj(L"STATIC", L"H CARD", 10 , 610, w*2, h);
	drawObj(L"STATIC", L"L CARD", 10 , 630, w*2, h);
	drawObj(L"STATIC", L"KICK", 10 , 650, w*2, h);
	drawObj(L"STATIC", L"WIN", 10, 670, w * 2, h);
	


	for (int i = 0; i < 10; i++)
	{
		card1f[i] = drawObj(L"STATIC", NULL, 10+w * 2 + i*(w + 2), 590, w, h);
		card1c[i] = drawObj(L"STATIC", NULL,10+ w * 2 + i*(w + 2), 610, w, h);
		card2f[i] = drawObj(L"STATIC", NULL,10+ w * 2 + i*(w + 2), 630, w, h);
		card2c[i] = drawObj(L"STATIC", NULL,10+ w * 2 + i*(w + 2), 650, w, h);
		winner[i] = drawObj(L"STATIC", NULL, 10 + w * 2 + i*(w + 2), 670, w, h);
		
	}

	dealer=drawObj(L"STATIC", NULL, 10 ,690, w, h);
	actual= drawObj(L"STATIC", NULL, 10+w, 690, w, h);
	GS= drawObj(L"STATIC", NULL, 10+2*w, 690, w*4, h);
	SS= drawObj(L"STATIC", NULL, 10 + 6 * w,690, w * 4, h);
	return constObj;
}


void cDebugger::update()
{
	GD = hGP->GetGD();
	for (int i = 0; i < 10; i++)
	{/*
		SetWindowText(card1f[i], towstr(GD.player[i].fold).c_str());
		SetWindowText(card1c[i], towstr(GD.player[i].check).c_str());
		SetWindowText(card2f[i], towstr(GD.player[i].raise).c_str());
		SetWindowText(card2c[i], towstr(GD.player[i].allin).c_str());
		SetWindowText(value[i], towstr(GD.player[i].bet).c_str());
		

		SetWindowText(card1f[i], towstr(GD.player[i].card1.f).c_str());
		SetWindowText(card1c[i], towstr(GD.player[i].card1.c).c_str());
		SetWindowText(card2f[i], towstr(GD.player[i].card2.f).c_str());
		SetWindowText(card2c[i], towstr(GD.player[i].card2.c).c_str());
		
		*/
		SetWindowText(card1f[i], towstr(GD.player[i].value.combination).c_str());
		SetWindowText(card1c[i], towstr(GD.player[i].value.highcard).c_str());
		SetWindowText(card2f[i], towstr(GD.player[i].value.lowcard).c_str());
		SetWindowText(card2c[i], towstr(GD.player[i].value.kicker).c_str());
		
		SetWindowText(winner[i], towstr(GD.player[i].winner).c_str());

	}
		SetWindowText(dealer, towstr(GD.dealer).c_str());
		SetWindowText(actual, towstr(GD.actual).c_str());
		SetWindowText(maxbet, towstr(GD.maxbet).c_str());
		switch (GD.eSS)
		{
		case SS_INIT:
		{
			SetWindowText(SS, L"INIT");
			break;

		}

		case SS_BIDDING:
		{SetWindowText(SS, L"BIDDING");

		break;

		}

		}
		switch (GD.eGS)
		{


		case GS_DEALER:
		{
			SetWindowText(GS, L"DEALER");
			break;

		}

		case GS_PREFLOP:
		{SetWindowText(GS, L"PREFLOP");

			break;

		}
		case GS_HUMAN:
		{SetWindowText(GS, L"HUMAN");
			break;
		}
		case GS_FLOP:
		{SetWindowText(GS, L"FLOP");
		break;

		}

		case GS_TURN:
		{SetWindowText(GS, L"TURN");
		break;

		}

		case GS_RIVER:
		{SetWindowText(GS, L"RIVER");
		break;

		}
		case GS_ENDTURN:
		{SetWindowText(GS, L"ENDTURN");
		break;

		}

		default:
			break;



		}




}
int cDebugger::Command(int x)
{	//sends a chosen seat to hGP

	return x;
}

int cDebugger::Timer(int x) { return 0; }

cDebugger::~cDebugger()
{
	for (int i = 0; i < 10; i++)
	{
		DestroyWindow(card1f[i]);
		DestroyWindow(card1c[i]);
		DestroyWindow(card2f[i]);
		DestroyWindow(card2c[i]);
		DestroyWindow(winner[i]);
	}
	for (int i = 0; i < constObj; i++)
	{
		if (hObj[i])
		{
			DestroyWindow(hObj[i]);
			hObj[i] = NULL;
		}
	}
	DestroyWindow(dealer);
	DestroyWindow(actual);
	DestroyWindow(GS);
	DestroyWindow(SS);
	hWSI->ReleaseScrIndex(index);
	hWSI = NULL;

}

