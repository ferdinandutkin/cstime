#include "pch.h"

#include "serial.h"

serial::serial(const char* portName) : errors{}, status{}, connected{false}
{

    //Try to connect to the given port throuh CreateFile
    this->_handle = CreateFileA(portName,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    //Check if the connection was successfull
    if (this->_handle == INVALID_HANDLE_VALUE)
    {
        //If not success full display an Error
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {

            //Print Error if neccessary
            printf("ERROR: Handle was not attached. Reason: %s not available.\n", portName);

        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else
    {
        //If connected we try to set the comm parametersz
        DCB dcbSerialParams = { 0 };

        //Try to get the current
        if (!GetCommState(this->_handle, &dcbSerialParams))
        {
            //If impossible, show an error
            printf("failed to get current serial parameters!");
        }
        else
        {
            //Define serial connection parameters for the arduino board
            dcbSerialParams.BaudRate = CBR_9600;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;
            //Setting the DTR to Control_Enable ensures that the Arduino is properly
            //reset upon establishing a connection
            dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

            //Set the parameters and check for their proper application
            if (!SetCommState(_handle, &dcbSerialParams))
            {
                printf("ALERT: Could not set Serial Port parameters");
            }
            else
            {
                //If everything went fine we're connected
                this->connected = true;
                //Flush any remaining characters in the buffers 
                PurgeComm(this->_handle, PURGE_RXCLEAR | PURGE_TXCLEAR);
                //We wait 2s as the arduino board will be reseting
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }

}

serial::~serial()
{
    //Check if we are connected before trying to disconnect
    if (this->connected)
    {
        //We're no longer connected
        this->connected = false;
        //Close the serial handler
        CloseHandle(this->_handle);
    }
}

int serial::read(char* buffer, unsigned int nbChar)
{
    //Number of bytes we'll have read
    DWORD bytesRead;
    //Number of bytes we'll really ask to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(this->_handle, &this->errors, &this->status);

    //Check if there is something to read
    if (this->status.cbInQue > 0)
    {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if (this->status.cbInQue > nbChar)
        {
            toRead = nbChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if (ReadFile(this->_handle, buffer, toRead, &bytesRead, NULL))
        {
            return bytesRead;
        }

    }

    //If nothing has been read, or that an error was detected return 0
    return 0;

}


bool serial::write(const char* buffer)
{
    DWORD bytesSend;

    //Try to write the buffer on the Serial port
    if (!WriteFile(this->_handle, (void*)buffer, strlen(buffer), &bytesSend, 0))
    {
        //In case it don't work get comm error and return false
        ClearCommError(this->_handle, &this->errors, &this->status);

        return false;
    }
    else
        return true;
}

bool serial::is_connected()
{
    //Simply return the connection status
    return this->connected;
}