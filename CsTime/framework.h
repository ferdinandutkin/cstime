#pragma once

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>

using user_message_hook = int (const char* name, int size, char* buffer);


struct user_message
{
    char unknown[8];
    char name[16];
    user_message* next;
    user_message_hook* handler;
}; 