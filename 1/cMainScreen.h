#pragma once
#include "stdafx.h"
//Implements few usefull methods for painting in mainscreen
class cMainScreen 
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

public:
	cMainScreen(HINSTANCE, HWND, HBITMAP=0);
	void rectupdate(HBITMAP, int, int, int, int,int,int,int=1);	
	void update(HBITMAP);
	void refresh();
	~cMainScreen();
		
};