#include "pch.h"

#include "framework.h"
#include "memory.h"
#include "globals.h"
#include <iostream>
#include "types.h"

user_message_hook* round_time_original = nullptr;
user_message_hook* bomb_drop_original = nullptr;
user_message_hook* bomb_pickup_original = nullptr;




int round_time_hooked(const char* name, int size, char* buffer)
{
    std::cout << name << std::endl;

    auto round_time = read<uint16_t>(buffer);
   
    std::cout << round_time << std::endl;
    
    return round_time_original(name, size, buffer);
}

int bomb_drop_hooked(const char* name, int size, char* buffer)
{
    std::cout << name << std::endl;
    
    auto [_0, _1, _2, planted] = read<uint16_t, uint16_t, uint16_t, byte_t>(buffer);
    
    std::cout << "planted: " << planted << std::endl;

    return bomb_drop_original(name, size, buffer);
}



int bomb_pickup_hooked(const char* name, int size, char* buffer)
{
    std::cout << name << std::endl;

    return bomb_drop_original(name, size, buffer);
}


 
void hook_user_messages()
{
 
    auto found = find_pattern(base_address_global, module_size_global, "\x8B\x35\x00\x00\x00\x00\x83\xC4\x30", "xx????xxx") + 2;

    auto user_message = **(struct user_message***)found;

    auto current_user_msg = user_message;



    while (current_user_msg)
    {

        std::cout << "msg found: " << current_user_msg->name << std::endl;
        std::cout << "msg absoulte: " << (address_t)current_user_msg << std::endl;

        std::cout << "handler from start: " << (address_t)(&(current_user_msg->handler)) - base_address_global << std::endl;


        if (strcmp(current_user_msg->name, "RoundTime") == 0) {
            round_time_original = current_user_msg->handler;
            current_user_msg->handler = round_time_hooked;
            std::cout << "hooked round time" << std::endl;
        }

        else if (strcmp(current_user_msg->name, "BombDrop") == 0) {
            bomb_drop_original = current_user_msg->handler;
            current_user_msg->handler = bomb_drop_hooked;
            std::cout << "hooked bomb drop" << std::endl;
        }

        else if (strcmp(current_user_msg->name, "BombPickup") == 0) {
            bomb_pickup_original = current_user_msg->handler;
            current_user_msg->handler = bomb_pickup_hooked;
            std::cout << "hooked bomb drop" << std::endl;
        }


        current_user_msg = current_user_msg->next;
    }




 

  

}