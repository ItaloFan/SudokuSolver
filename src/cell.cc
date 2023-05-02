#include "cell.h"

bool Cell::empty()
{
    return val_ == 0;
}

void Cell::set(int val)
{
    val_ = val;
}

int Cell::val()
{
    return val_;
}

void Cell::clear()
{
    val_ = 0;
}