#pragma once

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>
#include <fstream>
#include <optional>

using user_message_hook = int (const char* name, int size, char* buffer);

using engine_message_hook = void ();


struct user_message
{
    char unknown[8];
    char name[16];
    user_message* next;
    user_message_hook* handler;
}; 

struct enginemsg_s
{
    int id;
    char* name;
    engine_message_hook* handler;
};