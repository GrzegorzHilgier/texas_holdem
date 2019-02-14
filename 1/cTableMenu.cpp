#include"stdafx.h"

int cTableMenu::init2()
{
	/////Load card bitmap and setup card height and width
	hBitmapCards = (HBITMAP)LoadImage(hInst, L"cards2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hBitmapCards, sizeof(bitmap), &bitmap);
	cardwidth = (bitmap.bmWidth / CIR);
	cardheight = (bitmap.bmHeight / CIC);
	////// Load dealer bitmap and setup height and width
	hBitmapDealer = (HBITMAP)LoadImage(hInst, L"dealer.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hBitmapDealer, sizeof(bitmap), &bitmap);
	dealerwidth = bitmap.bmWidth;
	dealerheight = bitmap.bmHeight;
	//////Game Data handle
	hMS = hWSI->GethMS();
	hGP = dynamic_cast<cGameProcedure*>(hParrent);
	GD = hGP->GetGD();
	/////Global variable reset
	hAnime = NULL;
	iteration = 0;

	for (int i = 0; i < 6; i++)
	{

		if (GD.player[i].ingame == 1)
			hnickname[i] = drawObj(L"STATIC", hGP->nickname[i], player[i][0][0], player[i][0][1] + cardheight, cardwidth * 2, 20);
	}
	for (int i = 6; i < 10; i++)
	{

		if (GD.player[i].ingame == 1)
			hnickname[i] = drawObj(L"STATIC", hGP->nickname[i], player[i][0][0], player[i][0][1] - 21, cardwidth * 2, 20);
	}
	/*
		for (int i = 0; i < 10; i++)
		{

			if (GD.player[i].ingame == 1)
			{
				hstack[i] = drawObj(L"STATIC", towstr(GD.player[i].stack).c_str(), player[i][1][0], player[i][1][1], 50, 20);
				hbet[i]= drawObj(L"STATIC", towstr(GD.player[i].bet).c_str(), player[i][2][0], player[i][2][1], 50, 20);
			}
		}
		hglobalstack = drawObj(L"STATIC", towstr(GD.stack).c_str(), 485, 370, 50, 20);
		*/

	hMS->rectupdate(hBitmapCards, deck[0], deck[1], 0, 0, cardwidth, cardheight);
	dealerx = deck[0] + cardwidth + 10;
	dealery = deck[1] + (cardheight - dealerheight) / 2;
	hMS->rectupdate(hBitmapDealer, dealerx, dealery, 0, 0, dealerwidth, dealerheight);

	return constObj;
}
///usefull methods
void cTableMenu::StopTimer(int x)
{
	int ind;
	if (x == 0)ind = index;
	else ind = x;
	KillTimer(hWnd, ind);
}
void cTableMenu::StartTimer(int time, int x )
{
	int ind;
	if (x == 0)ind = index;
	else ind = x;
	int t = 10;
	if (time != 0)t = time;
	if (SetTimer(hWnd, ind, t, NULL) == 0)MessageBox(hWnd, L"timer error", L"", NULL);

}
void cTableMenu::DealerMove()
{
	hMS->rectupdate(NULL, dealerx, dealery, 0, 0, dealerwidth, dealerheight, 1);
	int nextx;
	int nexty;

	if (GD.dealer == 9 || GD.dealer == 0 || GD.dealer == 1)
	{
		nextx = x + player[GD.dealer][1][0] + (50 - dealerwidth) / 2;
		nexty = y + player[GD.dealer][1][1] + 22;
	}
	if (GD.dealer == 2 || GD.dealer == 3)
	{
		nextx = x + player[GD.dealer][1][0] - (2 + dealerwidth);
		nexty = y + player[GD.dealer][1][1];
	}
	if (GD.dealer == 4 || GD.dealer == 5 || GD.dealer == 6)
	{
		nextx = x + player[GD.dealer][1][0] + (50 - dealerwidth) / 2;
		nexty = y + player[GD.dealer][1][1] - 22;
	}
	if (GD.dealer == 7 || GD.dealer == 8)
	{
		nextx = x + player[GD.dealer][1][0] + 52;
		nexty = y + player[GD.dealer][1][1];
	}


	hAnime = new cAnimation(hBitmapDealer, dealerx, dealery, 0, 0, dealerwidth, dealerheight, nextx, nexty, 15);
	hAnime->init(hInst, hWnd, 0, 0, hWSI, this);

	dealerx = nextx;
	dealery = nexty;


}
void cTableMenu::inciteration()
{
	int counter;

	do
	{
		iteration++;
		if (iteration >= 20)counter = iteration - 20;
		else if (iteration >= 10)counter = iteration - 10;
		else counter = iteration;
	} while (GD.player[counter].card1.f == 0);
}
/// screen data update
void cTableMenu::CardUpdate()
{
	for (int i = 0; i < 10; i++)
	{
		if (GD.player[i].card1.f)
		{
			hMS->rectupdate(hBitmapCards, player[i][0][0], player[i][0][1], GD.player[i].card1.f - 1, GD.player[i].card1.c, cardwidth, cardheight);
			hMS->rectupdate(hBitmapCards, player[i][0][0] + cardwidth, player[i][0][1], GD.player[i].card2.f - 1, GD.player[i].card2.c, cardwidth, cardheight);
		}
		else
		{
			hMS->rectupdate(NULL, player[i][0][0], player[i][0][1], NULL, NULL, cardwidth, cardheight);
			hMS->rectupdate(NULL, player[i][0][0] + cardwidth, player[i][0][1], NULL, NULL, cardwidth, cardheight);
		}
	}
}
void cTableMenu::BetUpdate()
{
	for (int i = 0; i < 10; i++)
	{
		if (GD.player[i].ingame == 1 && GD.player[i].stack > 0)
		{
			if (hstack[i] == NULL)
				hstack[i] = drawObj(L"STATIC", towstr(GD.player[i].stack).c_str(), player[i][1][0], player[i][1][1], 50, 20);
			SetWindowText(hstack[i], towstr(GD.player[i].stack).c_str());
		}
		else
		{
			if (hstack[i])
			{
				DestroyWindow(hstack[i]);
				hstack[i] = NULL;
				constObj--;

			}

		}


		if (GD.player[i].ingame == 1 && GD.player[i].bet > 0)
		{
			if (hbet[i] == NULL)
				hbet[i] = drawObj(L"STATIC", towstr(GD.player[i].bet).c_str(), player[i][2][0], player[i][2][1], 50, 20);
			SetWindowText(hbet[i], towstr(GD.player[i].bet).c_str());
		}
		else
		{
			if (hbet[i])
			{
				DestroyWindow(hbet[i]);
				hbet[i] = NULL;
				constObj--;
			}
		}

		if (GD.player[i].ingame == 0)
		{
			if (hnickname[i])
			{
				DestroyWindow(hnickname[i]);
				hnickname[i] = NULL;
				constObj--;
			}
		}
	}

	if (GD.stack > 0)
	{
		if (hglobalstack == NULL)
			hglobalstack = drawObj(L"STATIC", towstr(GD.stack).c_str(), 485, 370, 50, 20);
		SetWindowText(hglobalstack, towstr(GD.stack).c_str());
	}
	else
	{
		if (hglobalstack)
		{
			DestroyWindow(hglobalstack);
			hglobalstack = NULL;
			constObj--;

		}

	}



}





/// animation procedures


void cTableMenu::DealerRollTimer(int t)
{
	if (t == index)
	{
		if (hAnime)
		{
			delete hAnime; hAnime = NULL;
		}
		if (iteration < 10)
		{

			if (GD.player[iteration].card1.f)
			{

				hAnime = new cAnimation(hBitmapCards, deck[0], deck[1], GD.player[iteration].card1.f - 1, GD.player[iteration].card1.c, cardwidth, cardheight, x + player[iteration][0][0] + cardwidth / 2, y + player[iteration][0][1]);
				hAnime->init(hInst, hWnd, 0, 0, hWSI, this);

			}
			inciteration();
		}
		else
		{
			StopTimer();

			StartTimer(2000, index + 1);
			iteration = 0;


		}
	}
	if (t == (index + 1))
	{
		StopTimer(index + 1);
		for (int i = 0; i < 10; i++)
		{
			hMS->rectupdate(NULL, x + player[i][0][0] + cardwidth / 2, y + player[i][0][1], NULL, NULL, cardwidth, cardheight);

		}
		//Restart GP timer
		hGP->StartTimer();


	}


}
void cTableMenu::TurnTimer()
{

	if (hAnime)
	{
		delete hAnime; hAnime = NULL;
	}
	if (iteration < 1)
	{
		hAnime = new cAnimation(hBitmapCards, deck[0], deck[1], GD.turn.f - 1, GD.turn.c, cardwidth, cardheight, deck[0] + cardwidth * 4, deck[1]);
		hAnime->init(hInst, hWnd, 0, 0, hWSI, this);
		iteration++;
	}
	else
	{
		StopTimer();

		hGP->StartTimer();
		iteration = 0;


	}

}
void cTableMenu::RiverTimer()
{

	if (hAnime)
	{
		delete hAnime; hAnime = NULL;
	}
	if (iteration < 1)
	{
		hAnime = new cAnimation(hBitmapCards, deck[0], deck[1], GD.river.f - 1, GD.river.c, cardwidth, cardheight, deck[0] + cardwidth * 5, deck[1]);
		hAnime->init(hInst, hWnd, 0, 0, hWSI, this);
		iteration++;
	}
	else
	{
		StopTimer();

		hGP->StartTimer();
		iteration = 0;


	}

}
void cTableMenu::FlopTimer(int t)
{
	if (hAnime)
	{
		delete hAnime; hAnime = NULL;
	}
	if (iteration < 3)
	{
		hAnime = new cAnimation(hBitmapCards, deck[0], deck[1], GD.flop[iteration].f - 1, GD.flop[iteration].c, cardwidth, cardheight, deck[0] + cardwidth * (iteration + 1), deck[1]);
		hAnime->init(hInst, hWnd, 0, 0, hWSI, this);
		iteration++;
	}
	else
	{
		StopTimer();

		hGP->StartTimer();
		iteration = 0;


	}

}

void cTableMenu::ShuffleTimer(int t)
{
	if (hAnime)
	{
		delete hAnime; hAnime = NULL;
	}

	int counter;
	if (iteration >= 20)counter = iteration - 20;
	else if (iteration >= 10)counter = iteration - 10;
	else counter = iteration;

	if (iteration == GD.dealer + 1)
		for (int i = 0; i < 10; i++)
		{
			hMS->rectupdate(NULL, player[i][0][0], player[i][0][1], NULL, NULL, cardwidth, cardheight);
			hMS->rectupdate(NULL, player[i][0][0] + cardwidth, player[i][0][1], NULL, NULL, cardwidth, cardheight);
			for (int j = 1; j < 6; j++)hMS->rectupdate(NULL, deck[0] + j * cardwidth, deck[1], NULL, NULL, cardwidth, cardheight);
		}
	if (iteration < (11 + GD.dealer))
	{

		if (GD.player[counter].card1.f)
		{
			hAnime = new cAnimation(hBitmapCards, deck[0], deck[1], GD.player[counter].card1.f - 1, GD.player[counter].card1.c, cardwidth, cardheight, x + player[counter][0][0], y + player[counter][0][1]);
			hAnime->init(hInst, hWnd, 0, 0, hWSI, this);
		}
		inciteration();
	}
	else if (iteration >= (11 + GD.dealer) && iteration < (21 + GD.dealer))
	{
		if (GD.player[counter].card1.f)
		{
			hAnime = new cAnimation(hBitmapCards, deck[0], deck[1], GD.player[counter].card2.f - 1, GD.player[counter].card2.c, cardwidth, cardheight, x + player[counter][0][0] + cardwidth, y + player[counter][0][1]);
			hAnime->init(hInst, hWnd, 0, 0, hWSI, this);
		}
		inciteration();

	}
	else
	{
		StopTimer(index);
		iteration = 0;
		hGP->StartTimer();

	}

}
void cTableMenu::EndturnTimer()
{
	StopTimer(index);
	BetUpdate();
	iteration = 0;
	hGP->StartTimer(1000);

}

void cTableMenu::Update()
{
	int time = 1000;
	hGP->StopTimer();
	GD = hGP->GetGD();
	if (GD.eSS == SS_BIDDING)
	{
		BetUpdate();
		CardUpdate();
		hGP->StartTimer(time);
	}
	else if (GD.eSS == SS_CLEAR)
	{
		BetUpdate();
		CardUpdate();
		hGP->StartTimer(time * 2);
	}
	else if (GD.eSS == SS_INIT)
	{

		iteration = 0;
		StartTimer(20);
		if (GD.eGS == GS_PREFLOP)
		{

			iteration = GD.dealer + 1;
			DealerMove();
		}


	}


}

int cTableMenu::Timer(int t)
{

	if (!hWSI->pause)
	{
		switch (GD.eGS)
		{
		case GS_DEALER:
			DealerRollTimer(t);
			break;
		case GS_PREFLOP:
			ShuffleTimer(t);
			break;
		case GS_FLOP:
			FlopTimer(t);
			break;
		case GS_TURN:
			TurnTimer();
			break;
		case GS_RIVER:
			RiverTimer();
			break;
		case GS_ENDTURN:
			EndturnTimer();
			break;
		}
	}
	return 0;
}

cTableMenu::~cTableMenu()
{
	DeleteObject(hBitmapCards);
	DeleteObject(hBitmapDealer);

	for (int i = 0; i < constObj; i++) DestroyWindow(hObj[i]);
	for (int i = 0; i < 10; i++)
	{
		if (hnickname[i])DestroyWindow(hnickname[i]);
		hnickname[i] = NULL;
		if (hstack[i])DestroyWindow(hstack[i]);
		hstack[i] = NULL;
	}


	if (hAnime) delete hAnime;
	hAnime = NULL;
	KillTimer(hWnd, index);
	hWSI->ReleaseScrIndex(index);
	hWSI = NULL;
}


