// 为输入puzzle提供可视化界面，参考https://github.com/mayerui/sudoku

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
#include "pos.h"
#include "keymap.h"

struct CellCursor
{
    int row;
    int col;
};

class Scene
{
public:
    bool confirm = false;

    Scene();
    bool set_val(Pos pos, int val);
    bool clear_val(Pos pos);
    void show();
    void reset();
    void input();
    std::string get_puzzle();

private:
    CellCursor cur_cell_{4, 4};
    int board_[81] = {0};
    KeyMap keymap_;

    void cls_();
    void print_underline_(int row = -1);
};

#endif