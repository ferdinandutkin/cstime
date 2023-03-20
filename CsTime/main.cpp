#include "pch.h"
#include "console.h"
#include <iostream>
#include "globals.h"

#include "memory.h"
#include "user_messages.h"




DWORD WINAPI hack_main() {

    create_console();

    Sleep(600);
    auto base_address = (DWORD)GetModuleHandleA("hw");

    auto module_size = get_module_size(base_address);
    
    auto end_address = base_address + module_size - 1;

  

    module_size_global = module_size;
    base_address_global = base_address;
    end_address_global = end_address;

#ifdef DEBUG
    std::cout << "base address: " << base_address << std::endl;
#endif



    engine_funcs_global = (cl_enginefuncs_s*)(find_pattern(base_address, module_size, "\x69\x6E\x76\x61\x6C\x69\x64\x20\x73\x6F\x75\x6E\x64\x20\x25\x69\x0A", "xxxxxxxxxxxxxxxxx") + 24);
    

#ifdef DEBUG
    std::cout << "Engine Funcs: " << (unsigned long)(engine_funcs_global) << std::endl;
#endif

    hook_user_messages();

   
   

    return false;

}