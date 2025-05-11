#ifndef Platform_H
#define Platform_H

#include "Enums.hpp"

#if defined(Win32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#include <windows.h>
#else
#include <thread>
#endif

class Platform 
{
public:
    Platform(const Platform&) = delete;
    Platform& operator=(const Platform&) = delete;

    static Platform& getInstance();

    const OS& getPlatform() const;

private:
    Platform(); // Private constructor to prevent instantiation
    ~Platform(); // Private destructor

    OS m_platform;
};

#endif