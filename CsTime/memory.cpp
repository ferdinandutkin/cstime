#include "pch.h"
#include "memory.h"
#include <iostream>
#include "types.h"




bool test_sequence(const_byte_ptr_t sequence, const_byte_ptr_t target, const_byte_ptr_t mask) {
    for (; *mask; ++mask, ++sequence, ++target) {
        if (*mask == 'x' && *sequence != *target) {
            return false;
        }      
    }   
    return *mask;
}


byte_ptr_t find_pattern(address_t address, address_diff_t max_length, const_byte_ptr_t target, const_byte_ptr_t mask) {
    for (address_t i = 0; i < max_length; i++) {
        if (test_sequence((byte_ptr_t)address + i, target, mask)) {
            return (byte_ptr_t)address + i;
        }
    }          
    return nullptr;
}

address_diff_t get_module_size(address_t address)
{
    return PIMAGE_NT_HEADERS(address + (address_t)PIMAGE_DOS_HEADER(address)->e_lfanew)->OptionalHeader.SizeOfImage;
}


