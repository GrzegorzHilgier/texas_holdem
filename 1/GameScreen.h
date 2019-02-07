#pragma once
#include"stdafx.h"

#include "Screen.h"
class GameScreen : public Screen
{
private:
	HBITMAP hBitmapMain;
	HBITMAP hBitmapUpdate;
	BITMAP  bitmap;
	HDC     hdcCurrent;
	HDC hdc, hdcNEW;
	HGDIOBJ   old_hdcCurrent, old_hdcNEW;
	PAINTSTRUCT ps;
	HINSTANCE hInst;
	HWND hWnd;
	HWND hPrzycisk1;
	HWND hPrzycisk2;
	HWND hPrzycisk3;
	HWND hStatic;
	HWND hScroll;
	int ID_PRZYCISK1 ;
	int ID_PRZYCISK2 ;
	int ID_PRZYCISK3;
	
	bool flag = 0;


public:



	void init(HINSTANCE hInstt, HWND hWndd);
	
	GameScreen();
	
	void action();
	


	int hmi(int CM_Command);
	
	void update();
	
	void refresh();
	

	~GameScreen();
	
};