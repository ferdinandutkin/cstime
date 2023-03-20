#pragma once
#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED

#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class serial
{
private:
    //Serial comm handler
    HANDLE _handle;
    //Connection status
    bool connected;
    //Get various information about the connection
    COMSTAT status;
    //Keep track of last error
    DWORD errors;

public:
    //Initialize Serial communication with the given COM port
    serial(const char* portName);
    //Close the connection
    ~serial();
    //Read data in a buffer, if nbChar is greater than the
    //maximum number of bytes available, it will return only the
    //bytes available. The function return -1 when nothing could
    //be read, the number of bytes actually read.
    int read(char* buffer, unsigned int nbChar);
    //Writes data from a buffer through the Serial connection
    //return true on success.
    bool write(const char* buffer);
    //Check if we are actually connected
    bool is_connected();


};

#endif // SERIALCLASS_H_INCLUDED
