#include "pch.h"
#include "memory.h"
#include <iostream>
#include "types.h"




bool test_sequence(const_byte_ptr_t data, const_byte_ptr_t pattern, const_byte_ptr_t mask) {
    for (; *mask; ++mask, ++data, ++pattern)
        if (*mask == 'x' && *data != *pattern)
            return false;
    return (*mask) == 0;
}

byte_ptr_t find_pattern(address_t address, address_diff_t len, const_byte_ptr_t pattern, const_byte_ptr_t mask) {
    for (unsigned long i = 0; i < len; i++)
        if (test_sequence((const char*)address + i, pattern, mask))
            return (byte_t*)address + i;
    return nullptr;
}


address_diff_t get_module_size(address_t address)
{
    return PIMAGE_NT_HEADERS(address + (address_t)PIMAGE_DOS_HEADER(address)->e_lfanew)->OptionalHeader.SizeOfImage;
}


