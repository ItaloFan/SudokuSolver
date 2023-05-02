#ifndef POS_H
#define POS_H

class Pos
{
public:
    Pos();
    Pos(int row, int col);
    Pos(int idx);

    int row;
    int col;
    int box;
    int idx;
};

#endif