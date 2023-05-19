#ifndef COMMON_H
#define COMMON_H

#include <iostream>

// 位操作
constexpr uint32_t kAll = 0x1ff; // 9 bits
inline uint32_t GetLowBit(uint32_t x)
{
    return x & -x;
}

inline uint32_t LowOrderBitIndex(uint32_t x)
{
    return __builtin_ctz(x);
}

inline uint32_t ClearLowBit(uint32_t x)
{
    return x & (x - 1);
}

inline int NumBitsSet(uint32_t n)
{
    int count = 0;
    while (n)
    {
        count++;
        n &= (n - 1);
    }
    return count;
}
#endif

#ifndef VERTICAL_LINE
#define VERTICAL_LINE "\u2503"
#endif
#ifndef HORIZONTAL_LINE
#define HORIZONTAL_LINE "\u2501"
#endif
#ifndef CROSS_LINE
#define CROSS_LINE "\u254B"
#endif