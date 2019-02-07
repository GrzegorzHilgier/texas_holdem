#include "stdafx.h"
#define ITERATION 6 

cAnimation::cAnimation(HBITMAP h, int xstart, int ystart, int xinn, int yinn, int widthh, int heightt, int xstopp, int ystopp,int framess)
{
	if (framess > 0)frames = framess;
	else frames = ITERATION;
	hBitmap = h;
	iteration = 0;

	xin = xinn;
	yin = yinn;
	width = widthh;
	height = heightt;
	xstop = xstopp;
	ystop = ystopp;

	xvect = (xstop - xstart) / frames;
	yvect = (ystop - ystart) / frames;
	xcurrent = xstart+xvect;
	ycurrent = ystart+yvect;

}
int cAnimation::init2()
{
	
	hMS=hWSI->GethMS();
	hTableMenu = dynamic_cast<cTableMenu*>(hParrent);
	hTableMenu->StopTimer();
	iteration = 0;
	if(SetTimer(hWnd, index, 20, NULL)==NULL)MessageBox(hWnd, L"timer error", L"", NULL);
	
	return 0;


}



int cAnimation::Timer(int t)
{

	if (!hWSI->pause)
	{

		if (iteration < frames)
		{
			if (iteration) hMS->rectupdate(NULL, xcurrent - xvect, ycurrent - yvect, xin, yin, width, height, 0);

			hMS->rectupdate(hBitmap, xcurrent, ycurrent, xin, yin, width, height, 0);
			xcurrent = xcurrent + xvect;
			ycurrent = ycurrent + yvect;
			iteration++;
		}
		else
		{

			KillTimer(hWnd, index);
			hMS->rectupdate(NULL, xcurrent - xvect, ycurrent - yvect, xin, yin, width, height, 0);
			hMS->rectupdate(hBitmap, xstop, ystop, xin, yin, width, height);
			iteration = 0;
			hTableMenu->StartTimer();




		}
	}
	return 0;

}

cAnimation::~cAnimation()
{
	
	hWSI->ReleaseScrIndex(index);
	KillTimer(hWnd, index);
}
