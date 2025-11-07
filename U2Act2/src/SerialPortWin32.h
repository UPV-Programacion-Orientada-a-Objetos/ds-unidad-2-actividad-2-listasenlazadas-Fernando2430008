/**
 * @file SerialPortWin32.h
 * @brief Comunicación serial básica en Windows sin STL.
 */
#pragma once

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>

class SerialPortWin32 {
#ifdef _WIN32
    HANDLE h;
#endif
public:
    SerialPortWin32();
    ~SerialPortWin32();

    bool open(const char* portName, unsigned long baud);
    void close();
    /** Lee una línea (terminada en \n o \r\n) hasta maxLen-1 y la termina con \0. Devuelve true si obtuvo algo. */
    bool readLine(char* outBuf, size_t maxLen, unsigned long timeoutMs);
};
