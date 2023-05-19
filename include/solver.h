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
    bool valid_puzzle();
    bool solve();
    int guesses();
    double solve_time();
    void print_board();
    // 替换不同的占位符为0
    static void replace(std::string &puzzle, char oldc, char newc);
    // 判断输入是否合法
    static bool valid_string(std::string puzzle);

private:
    std::vector<int> str2num_(const std::string &puzzle);
    bool brute_force_solve_(uint32_t todo_idx);
    int count_solution_(uint32_t todo_idx);
    int num_candidates_(const Pos &pos);
    void move_best_todo_to_front_(uint32_t todo_index);

    Cell board_[9][9];
    Block rows_[9];
    Block cols_[9];
    Block boxes_[9];
    std::vector<Pos> cells_todo_;
    size_t num_guesses_{0};
    size_t num_todo_{0};
    size_t solution_count_{0};
    double duration_ = 0; // 解题时间
};

#endif