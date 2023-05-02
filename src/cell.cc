#include "cell.h"

bool Cell::empty()
{
    return _val == 0;
}

void Cell::set(int val)
{
    _val = val;
}

int Cell::val()
{
    return _val;
}

void Cell::clear()
{
    _val = 0;
}