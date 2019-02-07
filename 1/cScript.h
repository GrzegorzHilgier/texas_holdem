#pragma once
#include "stdafx.h"
class WSInterface;





//parent class for menu objects
class cScript
{ protected:
	HWND hWnd;
	HINSTANCE hInst;
	WSInterface* hWSI;
	cScript* hParrent;
	int index;
	
	HWND hObj[MAX_SCRIPT_OBJECTS];
	int constObj;
	int x, y;
	
public:
	
	virtual int init2() = 0;
	int init(HINSTANCE, HWND, int, int, WSInterface*,cScript*);


	HWND drawObj(LPCWSTR , LPCWSTR , int , int , int , int, int=1 );
	
	std::wstring towstr(const std::string&);
	std::wstring towstr(int );
	virtual int Command(int) =0;
	virtual int Timer(int) = 0;
	virtual int Scroll(int) = 0;
	virtual ~cScript() {};
};




