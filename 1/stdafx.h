// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>


// TODO: reference additional headers your program requires here

#define USER_OBJECTS_CODE 500
#define MAX_SCRIPTS 10
#define MAX_SCRIPT_OBJECTS 100
#define MAX_NICKNAME 10


class cScript;
class cMainMenu;
class cMainScreen;
class cSeatMenu;
class csubMenu;
class cTableMenu;
class WSInterface;
class cSeatMenu;
class cSubMenu1;
class cDebugger;
class cGameProcedure;
class cBetMenu;

#include "cGameEngine.h"
#include "Structures.h"
#include "cScript.h"
#include "cMainScreen.h"
#include "WSInterface.h"

#include "cGameProcedure.h"
#include "cDebugger.h"
#include "cSeatMenu.h"
#include "cBetMenu.h"
#include "cAnimation.h"
#include "cTableMenu.h"

#include "cSubMenu1.h"
#include "cMainMenu.h"




