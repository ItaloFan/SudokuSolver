// 平台相关代码
#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
#include <conio.h>
#else
#ifdef __linux__
#include <termio.h>
#include <cstdio>
#elif __APPLE__
#include <termios.h>
#endif
#endif

inline void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#endif