#pragma once
#include "stdafx.h"
//Implements movement animation of object BITMAP from start coords to stop coords
//TODO: change constructor -several ints into points or vector object
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