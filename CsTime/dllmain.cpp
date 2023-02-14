// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"

#include "framework.h"


#include "cl_clientfuncs_s.h"
#include "user_messages.h"
#include <fstream>
#include <iostream>
#include "globals.h"
#include "memory.h"
#include "console.h"









cl_enginefuncs_s* gendo;



static pfnUserMsgHook TeamInfoOrg = NULL;

 







BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{

   return true;
}




