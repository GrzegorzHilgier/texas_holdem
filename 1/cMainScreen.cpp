
#include "stdafx.h"


cMainScreen::cMainScreen(HINSTANCE hInstt, HWND hWndd,HBITMAP h)
{

	hInst = hInstt;
	hWnd = hWndd;
	

	//wgranie bitmap
	if (h) hBitmapMain = h;
	else hBitmapMain = (HBITMAP)LoadImage(hInst, L"main.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	hdc = GetDC(hWnd);
	//zaladowanie do bufora hdccurrent domyslnej bitmapy
	hdcCurrent = CreateCompatibleDC(hdc);
	SetStretchBltMode(hdcCurrent, COLORONCOLOR);
	//zapamietanie starej domyslnej bitmapy z elementu hdccurrent
	old_hdcCurrent = SelectObject(hdcCurrent, hBitmapMain);

	GetObject(hBitmapMain, sizeof(bitmap), &bitmap);
	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcCurrent, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
	


}



void cMainScreen::rectupdate(HBITMAP h, int xout, int yout, int xin, int yin,int width, int height, int remember)
{
	
		HBITMAP update;
		if(h)update = h;
		else update = hBitmapMain;
		
		hdc = GetDC(hWnd);
		hdcNEW = CreateCompatibleDC(hdc);
		HBITMAP old = (HBITMAP)SelectObject(hdcNEW, update);

		if (h)
		{
			if(remember)BitBlt(hdcCurrent, xout, yout, width, height, hdcNEW, xin*width, yin* height, SRCCOPY);
			BitBlt(hdc, xout, yout, width, height, hdcNEW, xin*width, yin* height, SRCCOPY);
			
		}

		else
		{
			if (remember)BitBlt(hdcCurrent, xout, yout, width, height, hdcNEW, xout, yout, SRCCOPY);
			BitBlt(hdc, xout, yout, width, height, hdcCurrent, xout, yout, SRCCOPY);

		}

/*
		if (remember)BitBlt(hdcCurrent, xout, yout, width, height, hdcNEW, xin*width, yin* height, SRCCOPY);
		if(h)BitBlt(hdc, xout, yout, width, height, hdcNEW, xin*width, yin* height, SRCCOPY);
		else BitBlt(hdc, xout, yout, width, height, hdcCurrent, xout, yout, SRCCOPY);
*/		

		ReleaseDC(hWnd, hdc);
		SelectObject(hdcNEW, old);
		DeleteDC(hdcNEW);
}





void cMainScreen::update(HBITMAP h)
{
	if (h)
	{
		hBitmapUpdate = h;
		hBitmapMain = h;
	}
	else hBitmapUpdate = hBitmapMain;
	hdc = GetDC(hWnd);
	hdcNEW = CreateCompatibleDC(hdc);
	old_hdcNEW = SelectObject(hdcNEW, hBitmapUpdate);
	GetObject(hBitmapUpdate, sizeof(bitmap), &bitmap);
	
	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcNEW, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
	BitBlt(hdcCurrent, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcNEW, 0, 0, SRCCOPY);
	SelectObject(hdcNEW, old_hdcNEW);
	DeleteDC(hdcNEW);

	

	refresh();
}




void cMainScreen::refresh()
{

	hdc = BeginPaint(hWnd, &ps);
	GetObject(hBitmapMain, sizeof(bitmap), &bitmap);
	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcCurrent, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
	EndPaint(hWnd, &ps);
}

cMainScreen::~cMainScreen()
{
	
	SelectObject(hdcCurrent, old_hdcCurrent);
	ReleaseDC(hWnd, hdcCurrent);
	DeleteObject(hBitmapMain);
	DeleteObject(hBitmapUpdate);

}
