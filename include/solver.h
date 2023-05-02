#ifndef SOLVER_H
#define SOLVER_H

#include <string>
#include <stack>
#include "cell.h"
#include "block.h"
#include "pos.h"
#include "operate.h"

class Solver
{
public:
    Solver();
    Solver(std::string puzzle);
    void init(std::string puzzle);
    bool fill(const Pos &pos, int num);
    bool fill(int row, int col, int num);
    void clear(const Pos &pos);
    void clear(int row, int col);
    void clearAll();
    bool solve();
    double solve_time();
    int guesses();
    bool full();
    void print_board();
    // 替换不同的占位符为0
    static void replace(std::string &puzzle, char oldc, char newc);
    // 判断输入是否合法
    static bool valid(std::string puzzle);

private:
    std::vector<int> _str2num(const std::string &puzzle);
    bool _satisfyGivenPartialAssignment(uint32_t todo_idx);
    int _num_candidates(const Pos &pos);
    void _move_best_todo_to_front(uint32_t todo_index);

    Cell _board[9][9];
    Block _rows[9];
    Block _cols[9];
    Block _boxes[9];
    std::vector<Pos> _cells_todo;
    size_t _num_guesses{0};
    size_t _num_todo{0};
    double _duration = 0; // 解题时间
};

#endif