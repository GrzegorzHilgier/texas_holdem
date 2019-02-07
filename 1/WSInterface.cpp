
#include "stdafx.h"




WSInterface::WSInterface(HINSTANCE hInstt, HWND hWndd)
{
	//global window and instance handle
	hInst = hInstt;
	hWnd = hWndd;
	hMS = NULL;
	hGameProcedure = NULL;
	hMS = new cMainScreen(hInst, hWnd);
	for (int i = 0; i < MAX_SCRIPTS; i++) ScrMask[i] = 0;
	hGameProcedure = new cGameProcedure();
	hGameProcedure->init(hInst, hWnd, 0, 0, this, this);
	pause = 0;
}

WSInterface::~WSInterface()
{
	if (hGameProcedure) delete hGameProcedure;
	hGameProcedure = NULL;
	if (hMS)delete hMS;
	hMS = NULL;
}

int WSInterface::GetIndex(cScript* hScript)
{
	int result = 0;
	
	for (int i = 0; i < MAX_SCRIPTS; i++)
		if (ScrMask[i] == 0)
		{
			result = i;
			ScrMask[i] = hScript;
			break;
		}
	if (result<0 || result>MAX_SCRIPTS)MessageBox(hWnd, L"INDEX ERROR", towstr(result).c_str(),NULL);
	return(result*MAX_SCRIPT_OBJECTS + USER_OBJECTS_CODE);
}

void WSInterface::ReleaseScrIndex(int index)
{
	int i = (index - USER_OBJECTS_CODE) / MAX_SCRIPT_OBJECTS;
	if (i >= 0 && i < MAX_SCRIPTS)		
	ScrMask[i] = 0;
}


void WSInterface::refresh()
{
	if (hMS)hMS->refresh();
}


int WSInterface::Command(int CM_Command)
{
	if(CM_Command>= USER_OBJECTS_CODE&& CM_Command<= USER_OBJECTS_CODE+MAX_SCRIPTS*MAX_SCRIPT_OBJECTS)
		if (ScrMask[(CM_Command - USER_OBJECTS_CODE) / MAX_SCRIPT_OBJECTS])
	  ScrMask[(CM_Command - USER_OBJECTS_CODE) / MAX_SCRIPT_OBJECTS ]->Command(CM_Command);
	
	return 0;
}

int WSInterface::Timer(int T_Command) 
{ 
	if (T_Command >= USER_OBJECTS_CODE&& T_Command <= USER_OBJECTS_CODE + MAX_SCRIPTS*MAX_SCRIPT_OBJECTS)
		if(ScrMask[(T_Command - USER_OBJECTS_CODE) / MAX_SCRIPT_OBJECTS])
		ScrMask[(T_Command - USER_OBJECTS_CODE) / MAX_SCRIPT_OBJECTS]->Timer(T_Command);
	return 0;

}
void WSInterface::RegisterScroll(cScript* s)
{
	hScript = s;
}
int WSInterface::Scroll(int wParam)
{
	if (hScript) hScript->Scroll(wParam);
	return wParam;


}
cMainScreen* WSInterface::GethMS()
{
	return hMS;
}
cGameProcedure* WSInterface::GethGP()
{
	return hGameProcedure;

}