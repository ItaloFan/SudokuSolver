// 暂时未使用
#ifndef OPERATE_H
#define OPERATE_H

class Operate
{
public:
    Operate();
    Operate(int row, int col, int num) : row(row), col(col), num(num){};

    int row;
    int col;
    int num;
};

#endif