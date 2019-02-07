#pragma once
#include "stdafx.h"
class Screen
{

public:
	virtual void refresh() = 0;
	virtual void update() = 0;
	virtual void init(HINSTANCE, HWND) = 0;
	//virtual int hmi(int) = 0;
	virtual ~Screen() {};

};