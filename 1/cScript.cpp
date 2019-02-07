#include "stdafx.h"


int cScript::init(HINSTANCE hInstt, HWND hWndd, int xin, int yin, WSInterface  * hWSIntefrace, cScript* hP)
{
	hInst = hInstt;
	hWnd = hWndd;
	hParrent = hP;
//	hSubMenu = NULL;
	hWSI = hWSIntefrace;
	x = xin;
	y = yin;
	if (hWSI)index = hWSI->GetIndex(this);
	
	constObj = 0;
	int result = init2();
	
	return result;
}


HWND cScript::drawObj(LPCWSTR type, LPCWSTR name, int xx, int yy, int width, int heigh, int visible)
{
	HWND hwnd = NULL;
	if (constObj < MAX_SCRIPT_OBJECTS)
	{
		

		int z = constObj + index;
		//MessageBox(hWnd, towstr(z).c_str(), L"BUTTON_ID", MB_ICONINFORMATION);
		if (visible == 1)hObj[constObj] =hwnd= CreateWindowEx(0, type, name, WS_CHILD | WS_VISIBLE | WS_BORDER,
			x + xx, y + yy, width, heigh, hWnd, (HMENU)z, hInst, NULL);
		else hObj[constObj] =hwnd= CreateWindowEx(0, type, name, WS_CHILD | WS_BORDER,
			x + xx, y + yy, width, heigh, hWnd, (HMENU)z, hInst, NULL);
		

		constObj++;

		
	}
	return hwnd;
}

std::wstring cScript::towstr(const std::string& s)
{


	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);

	LPCWSTR wr = r.c_str();
	delete[] buf;
	return wr;

}
std::wstring cScript::towstr(int k)
{
	const std::string ss = (const std::string) std::to_string(k);
	const std::string& s = ss;

	return(towstr(ss));

}












	
