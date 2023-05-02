#include "block.h"

Block::Block()
{
}

bool Block::exist(int num)
{
    std::cout << "Unfinished Function Block::exist" << std::endl;
    return false;
}

std::vector<int> Block::getMiss()
{
    std::vector<int> miss;
    for (int i = 1; i <= 9; i++)
    {
        if (!exist(i))
        {
            miss.push_back(i);
        }
    }
    return miss;
}

void Block::bit_xor(uint32_t val)
{
    _bitmask ^= val;
}

void Block::bit_and(uint32_t val)
{
    _bitmask &= val;
}

uint32_t Block::bit_mask()
{
    return _bitmask;
}

void Block::bit_or(uint32_t val)
{
    _bitmask |= val;
}
