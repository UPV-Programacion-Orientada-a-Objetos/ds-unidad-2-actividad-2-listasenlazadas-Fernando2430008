#include "SerialPortWin32.h"

SerialPortWin32::SerialPortWin32() {
#ifdef _WIN32
    h = INVALID_HANDLE_VALUE;
#endif
}

SerialPortWin32::~SerialPortWin32() {
    close();
}

bool SerialPortWin32::open(const char* portName, unsigned long baud) {
#ifndef _WIN32
    (void)portName; (void)baud; return false;
#else
    // Formatear nombre: \\.\COMx
    char device[64];
    int needPrefix = 1;
    if (portName && (portName[0] == '\\\\')) needPrefix = 0; // ya viene prefijado
    if (needPrefix) {
        snprintf(device, sizeof(device), "\\\\.\\%s", portName);
    } else {
        snprintf(device, sizeof(device), "%s", portName);
    }

    h = CreateFileA(device, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (h == INVALID_HANDLE_VALUE) return false;

    DCB dcb; ZeroMemory(&dcb, sizeof(dcb)); dcb.DCBlength = sizeof(dcb);
    if (!GetCommState(h, &dcb)) { close(); return false; }
    dcb.BaudRate = baud;
    dcb.ByteSize = 8;
    dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl = DTR_CONTROL_DISABLE;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
    if (!SetCommState(h, &dcb)) { close(); return false; }

    COMMTIMEOUTS to;
    to.ReadIntervalTimeout = 50;           // ms entre bytes
    to.ReadTotalTimeoutMultiplier = 0;     
    to.ReadTotalTimeoutConstant = 50;      // timeout base de lectura
    to.WriteTotalTimeoutMultiplier = 10;
    to.WriteTotalTimeoutConstant = 100;
    if (!SetCommTimeouts(h, &to)) { close(); return false; }

    SetupComm(h, 4096, 4096);
    PurgeComm(h, PURGE_RXCLEAR | PURGE_TXCLEAR);

    return true;
#endif
}

void SerialPortWin32::close() {
#ifdef _WIN32
    if (h != INVALID_HANDLE_VALUE) {
        CloseHandle(h);
        h = INVALID_HANDLE_VALUE;
    }
#endif
}

bool SerialPortWin32::readLine(char* outBuf, size_t maxLen, unsigned long timeoutMs) {
#ifndef _WIN32
    (void)outBuf; (void)maxLen; (void)timeoutMs; return false;
#else
    if (h == INVALID_HANDLE_VALUE || !outBuf || maxLen == 0) return false;
    DWORD startTick = (timeoutMs > 0) ? GetTickCount() : 0;
    size_t idx = 0;
    while (1) {
        char ch;
        DWORD br = 0;
        if (!ReadFile(h, &ch, 1, &br, NULL)) return false;
        if (br == 1) {
            if (ch == '\r') {
                // mirar si viene \n después, pero terminar ya
                outBuf[idx] = '\0';
                return idx > 0;
            }
            if (ch == '\n') {
                outBuf[idx] = '\0';
                return idx > 0;
            }
            if (idx + 1 < maxLen) {
                outBuf[idx++] = ch;
            }
        }
        if (timeoutMs > 0) {
            DWORD elapsed = GetTickCount() - startTick;
            if (elapsed >= timeoutMs) {
                if (idx > 0) { outBuf[idx] = '\0'; return true; }
                return false;
            }
        }
        // pequeña espera activa
        Sleep(1);
    }
#endif
}
