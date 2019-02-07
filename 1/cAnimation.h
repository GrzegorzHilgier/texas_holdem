#pragma once
#include "stdafx.h"
class cAnimation:public cScript
{
	int iteration;
	int xcurrent;
	int ycurrent;
	int xvect;
	int yvect;
	int xin;
	int yin;
	int width;
	int height;
	int xstop;
	int ystop;
	int frames;
	HBITMAP hBitmap;
	cTableMenu* hTableMenu;
	cMainScreen* hMS;
public:
	cAnimation(HBITMAP , int , int , int , int , int , int , int , int ,int=0);
	int init2();
	int Command(int c) { return 0; }
	int Timer(int t);
	int Scroll(int k) { return 0; }
				
	~cAnimation();

};