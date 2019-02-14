#pragma once
#include "stdafx.h"
//Implements movement animation of rectangle from BITMAP over main screen from start coords to stop coords
//TODO change constructor parameters to vector instead of several integers
class cAnimation:public cMenu
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

	int init2();
	int Command(int c) { return 0; }
	int Timer(int t);
	int Scroll(int k) { return 0; }

public:
	//TODO: cAnimation(HBITMAP,Vector,Rectangle)
	cAnimation(HBITMAP h, int xstart, int ystart, int xinn, int yinn, int width, int height, int xstop, int ystop, int frames = 0);
			
	~cAnimation();
};