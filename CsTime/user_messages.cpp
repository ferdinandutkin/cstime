#include "pch.h"

#include "framework.h"
#include "memory.h"
#include "globals.h"
#include <iostream>
#include <format>
#include "types.h"
#include "serial.h"



user_message_hook* round_time_original = nullptr;
user_message_hook* bomb_drop_original = nullptr;
user_message_hook* bomb_pickup_original = nullptr;



char* map_name = nullptr;

volatile uint16_t round_time = 0;

volatile uint16_t bomb_time = 0;

serial port { "\\\\.\\COM5" };

#define COM
#define DEBUG
#define CON

void output(std::string str) {
#ifdef COM
    port.write((str + '\n').c_str());
#endif

#ifdef CON
    std::cout << str << std::endl;
#endif
}



int round_time_hooked(const char* name, int size, char* buffer)
{

    auto round_time = read<uint16_t>(buffer);

#ifdef DEBUG
  
    std::cout << name << std::endl;
    std::cout << round_time << std::endl;
#endif

    ::round_time = round_time;

    return round_time_original(name, size, buffer);
}




int bomb_drop_hooked(const char* name, int size, char* buffer)
{
#ifdef DEBUG
    std::cout << name << std::endl;
#endif

    auto [_0, _1, _2, dropped] = read<uint16_t, uint16_t, uint16_t, byte_t>(buffer);

    //if (!dropped) {
        ::bomb_time = 45;
    //}


    return bomb_drop_original(name, size, buffer);
}






int bomb_pickup_hooked(const char* name, int size, char* buffer)
{
    std::cout << name << std::endl;

    return bomb_drop_original(name, size, buffer);
}


void update_timer() {
    while (true) {
        Sleep(1000);
        if (round_time) {
            round_time--;
        }
        if (bomb_time) {
            bomb_time--;
        }
    }
}

std::string format_time(int seconds) {

    return std::format("{:02}:{:02}", seconds / 60, seconds % 60);
    
}
void print_timer() {
    while (true) {
        Sleep(1000);
      
    
        auto timer_string = std::format("{};{};{}", map_name, format_time(round_time), format_time(bomb_time));

        output(timer_string);
   
    }
}

void update_map_name() {
    while (true) {
        Sleep(1000);
        map_name = engine_funcs_global->pfnGetCvarPointer("HostMap")->string;
     
    }
}


void hook_user_messages()
{


    if (port.is_connected())
    {
#ifdef DEBUG
        std::cout << "connected" << std::endl;
#endif
    }
    else {
#ifdef DEBUG
        std::cout << "error: " << GetLastError();
#endif
    }

  

    auto found = find_pattern(base_address_global, module_size_global, "\x8B\x35\x00\x00\x00\x00\x83\xC4\x30", "xx????xxx") + 2;


    auto user_message = **(struct user_message***)found;

    auto current_user_msg = user_message;




    while (current_user_msg)
    {

#ifdef DEBUG
        std::cout << "msg found: " << current_user_msg->name << std::endl;
        std::cout << "msg absoulte: " << (address_t)current_user_msg << std::endl;

        std::cout << "handler from start: " << (address_t)(&(current_user_msg->handler)) - base_address_global << std::endl;
#endif

        


        if (strcmp(current_user_msg->name, "RoundTime") == 0) {
            round_time_original = current_user_msg->handler;
            current_user_msg->handler = round_time_hooked;

#ifdef DEBUG
            std::cout << "hooked round time" << std::endl;
#endif
        }

        else if (strcmp(current_user_msg->name, "BombDrop") == 0) {
            bomb_drop_original = current_user_msg->handler;
            current_user_msg->handler = bomb_drop_hooked;
#ifdef DEBUG
            std::cout << "hooked bomb drop" << std::endl;
#endif
        }

        else if (strcmp(current_user_msg->name, "BombPickup") == 0) {
            bomb_pickup_original = current_user_msg->handler;
            current_user_msg->handler = bomb_pickup_hooked;
#ifdef DEBUG
            std::cout << "hooked bomb drop" << std::endl;
#endif
        }


        current_user_msg = current_user_msg->next;
    }
   


    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)update_timer, 0, 0, 0);

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)print_timer, 0, 0, 0);


    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)update_map_name, 0, 0, 0);

}


