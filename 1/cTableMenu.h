#pragma once
#include "stdafx.h"
#define CIR 14
#define CIC 4

class cTableMenu : public cMenu
{

	// matrix with position of all components top left x,y for all players
	// {cards},{stack}{dealer}{bet}
	int player[10][3][2]=
	{
		{ {60,310},{160,340},{250,340} },
		{ {155,150},{255,250},{309,275} },
		{ {370,85},{392,200},{392,230} },
		{ {585,85},{584,200},{584,230} },
		{ {805,150},{730,250},{675,275} },
		{ {915,310},{820,340},{730,340} },
		{ {805,515},{730,436},{675,410} },
		{ {585,570},{584,475},{584,450} },
		{ {370, 570},{392,475},{392,450} },
		{ {155, 515},{255,436},{309,410} },


	};
	//position of deck,flop,turn,river
	int deck[2] = { 420,300 };

	//handles for players objects
	HWND hstack[10];
	HWND hnickname[10];
	HWND hbet[10];
	HWND hglobalstack;
	//handles
	cMainScreen* hMS;
	BITMAP  bitmap;
	HBITMAP hBitmapCards;
	HBITMAP hBitmapTable;
	HBITMAP hBitmapDealer;
	cAnimation* hAnime;
	
	cGameProcedure* hGP;
	sGameData GD; 
	
	//iteration used for updating player to be displayed by timer
	int iteration;
	int cardwidth;
	int cardheight;
	int dealerwidth;
	int dealerheight;
	int dealerx;
	int dealery;
	

	public:
	
		
		int init2();
		//usefull methods
		void StopTimer(int x = 0);
		void StartTimer(int time = 0, int x = 0);
		void DealerMove();
		void inciteration();
		// screen data update
		void CardUpdate();
		void BetUpdate();
		// animation procedures
		void DealerRollTimer(int t);
		void TurnTimer();
		void RiverTimer();
		void FlopTimer(int t);
		void ShuffleTimer(int t);
		void EndturnTimer();
		void Update();
		int Timer(int t);
		int Command(int x){return(0);}
		int Scroll(int k) { return 0; }		
		~cTableMenu();

	};