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
inline char getch(void)
{
    struct termios tmtemp, tm;
    char c;
    int fd = 0;
    if (tcgetattr(fd, &tm) != 0)
    { /*获取当前的终端属性设置，并保存到tm结构体中*/
        return -1;
    }
    tmtemp = tm;
    cfmakeraw(&tmtemp); /*将tetemp初始化为终端原始模式的属性设置*/
    if (tcsetattr(fd, TCSANOW, &tmtemp) != 0)
    { /*将终端设置为原始模式的设置*/
        return -1;
    }
    c = getchar();
    if (tcsetattr(fd, TCSANOW, &tm) != 0)
    { /*接收字符完毕后将终端设置回原来的属性*/
        return 0;
    }
    return c;
}
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