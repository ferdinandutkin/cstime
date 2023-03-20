#include "pch.h"
#include "AsiMain.h"
#include "main.h"



BOOL __stdcall RIB_Main(HPROVIDER provider_handle, U32 up_down, RIB_alloc_provider_handle_ptr RIB_alloc_provider_handle, RIB_register_interface_ptr RIB_register_interface, RIB_unregister_interface_ptr RIB_unregister_interface)
{

    if (up_down)
    {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)hack_main, 0, 0, 0);    
    }
    else
    {
        
        MessageBox(NULL, L"BYE", L"FROM INJECTED DLL", MB_OK);
    }
    return 1;
}
