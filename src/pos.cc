#include "pos.h"

Pos::Pos(int _row, int _col) : row(_row), col(_col)
{
    idx = row * 9 + col;
    box = row / 3 * 3 + col / 3;
}

Pos::Pos(int idx) : idx(idx)
{
    row = idx / 9;
    col = idx % 9;
    box = row / 3 * 3 + col / 3;
}