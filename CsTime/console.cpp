#include "pch.h"


#include <io.h>
#include <fcntl.h>
#include <iostream>

void create_console()
{ 
    AllocConsole();

    FILE* dummy_file;

    freopen_s(&dummy_file, "CONIN$", "r", stdin);
    freopen_s(&dummy_file, "CONOUT$", "w", stderr);
    freopen_s(&dummy_file, "CONOUT$", "w", stdout);

    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();
}