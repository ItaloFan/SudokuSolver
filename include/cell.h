#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    Cell(){};
    bool empty();
    void set(int value);
    int val();
    void clear();

private:
    int _val;
};

#endif