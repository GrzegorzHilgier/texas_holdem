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
	//prints rectangle(xin, yin, width, height) from HBITMAP onto mainscreen (xout,yout)
	void rectupdate(HBITMAP h, int xout, int yout, int xin, int yin, int width, int height, bool remember = TRUE);
	//updates whole main screen with HBITMAP
	void update(HBITMAP);
	void refresh();
	~cMainScreen();
		
};