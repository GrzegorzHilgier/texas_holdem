#include "stdafx.h"
#include "GameScreen.h"

void GameScreen::init(HINSTANCE hInstt, HWND hWndd)
{

	hInst = hInstt;
	hWnd = hWndd;

	hPrzycisk1 = CreateWindowEx(0, L"BUTTON", L"PASS", WS_CHILD | WS_VISIBLE,
		400, 650, 150, 30, hWnd, (HMENU)ID_PRZYCISK1, hInst, NULL);
	hPrzycisk2 = CreateWindowEx(0, L"BUTTON", L"BET", WS_CHILD | WS_VISIBLE,
		560, 650, 150, 30, hWnd, (HMENU)ID_PRZYCISK2, hInst, NULL);
	hPrzycisk2 = CreateWindowEx(0, L"BUTTON", L"All-IN!!", WS_CHILD | WS_VISIBLE,
		720, 650, 150, 30, hWnd, (HMENU)ID_PRZYCISK3, hInst, NULL);
	hStatic = CreateWindowEx(0, L"STATIC", L"HISTORY", WS_VSCROLL | WS_CHILD | WS_VISIBLE |
		SS_LEFT, 50, 550, 300, 150, hWnd, NULL, hInst, NULL);
	hScroll = CreateWindowEx(0, L"SCROLLBAR", NULL, WS_HSCROLL | WS_CHILD | WS_VISIBLE, 530, 600, 300, 20, hWnd, NULL, hInst, NULL);

	//wgranie bitmap
	hBitmapMain = (HBITMAP)LoadImage(hInst, L"GameScreen.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//hBitmapUpdate = (HBITMAP)LoadImage(hInst, L"cards.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//zaladowanie przyciskow


	hdc = GetDC(hWnd);
	//zaladowanie do bufora hdccurrent domyslnej bitmapy
	hdcCurrent = CreateCompatibleDC(hdc);
	//zapamietanie starej domyslnej bitmapy z elementu hdccurrent
	old_hdcCurrent = SelectObject(hdcCurrent, hBitmapMain);

	GetObject(hBitmapMain, sizeof(bitmap), &bitmap);
	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcCurrent, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);



}
GameScreen::GameScreen()
{

	int ID_PRZYCISK1 = 501;
	int ID_PRZYCISK2 = 502;
	int ID_PRZYCISK3 = 503;
}
void GameScreen::action()
{

}


int GameScreen::hmi(int CM_Command)
{

	if (CM_Command == 501) MessageBox(hWnd, L"Wcisn¹³eœ przycisk 1", L"test", MB_ICONINFORMATION);
	if (CM_Command == 502) MessageBox(hWnd, L"Wcisn¹³eœ przycisk 2", L"test", MB_ICONINFORMATION);
	return 0;
}
void GameScreen::update()
{
	hdcNEW = CreateCompatibleDC(GetDC(hWnd));
	old_hdcNEW = SelectObject(hdcNEW, hBitmapUpdate);
	hdc = GetDC(hWnd);
	BitBlt(hdc, 50, 50, 100, 100, hdcNEW, 50, 50, SRCCOPY);
	BitBlt(hdcCurrent, 50, 50, 100, 100, hdcNEW, 50, 50, SRCCOPY);

	SelectObject(hdcNEW, old_hdcNEW);
	DeleteDC(hdcNEW);
	ReleaseDC(hWnd, hdc);
}
void GameScreen::refresh()
{

	hdc = BeginPaint(hWnd, &ps);



	GetObject(hBitmapMain, sizeof(bitmap), &bitmap);
	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcCurrent, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
	EndPaint(hWnd, &ps);



}

GameScreen::~GameScreen()
{
	SelectObject(hdcCurrent, old_hdcCurrent);
	ReleaseDC(hWnd, hdcCurrent);
	DeleteObject(hBitmapMain);
	DeleteObject(hBitmapUpdate);
	DestroyWindow(hPrzycisk1);
	DestroyWindow(hPrzycisk2);
	DestroyWindow(hPrzycisk3);
}
