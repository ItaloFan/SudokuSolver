#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "cell.h"
#include "common.inl"

class Block
{
public:
    Block();
    bool exist(int num);
    // get missing nums
    std::vector<int> getMiss();
    void bit_xor(uint32_t value);
    void bit_or(uint32_t value);
    void bit_and(uint32_t value);
    uint32_t bit_mask();

private:
    // 9bit二进制数，1表示未填写
    uint32_t bitmask_{kAll};
};

#endif