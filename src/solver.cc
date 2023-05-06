#include "solver.h"
#include "pos.h"
#include "common.h"
#include <algorithm>
#include <iostream>
#include <array>
#include <chrono>
#include <unordered_set>

Solver::Solver()
{
    num_guesses_ = 0;
}

Solver::Solver(std::string puzzle)
{
    num_guesses_ = 0;
    init(puzzle);
}

void Solver::init(std::string puzzle)
{
    std::vector<int> nums = str2num_(puzzle);
    // fill 81 grid
    for (size_t i = 0; i < nums.size(); i++)
    {
        Pos pos = Pos(i);
        if (nums[i] > 0 && nums[i] <= 9)
        {
            board_[pos.row][pos.col].set(nums[i]);
            uint32_t value = 1u << (uint32_t)(nums[i] - 1);
            rows_[pos.row].bit_xor(value);
            cols_[pos.col].bit_xor(value);
            boxes_[pos.box].bit_xor(value);
        }
        else
        {
            board_[pos.row][pos.col].clear();
            cells_todo_.emplace_back(pos);
        }
    }
    num_todo_ = cells_todo_.size() - 1;
}
bool Solver::valid_puzzle()
{
    bool pass_valid = true;
    auto start_time = std::chrono::high_resolution_clock::now();

    // 判断重复数字的情况
    std::unordered_set<std::string> seen;
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            if (board_[i][j].empty())
                continue;
            int num = board_[i][j].val();
            std::string row = "row " + std::to_string(i) + " num " + std::to_string(num);
            std::string col = "col " + std::to_string(j) + " num " + std::to_string(num);
            std::string blk = "blk " + std::to_string(i / 3 * 3 + j / 3) + " num " + std::to_string(num);
            if (seen.count(row) || seen.count(col) || seen.count(blk))
            {
                std::cout << "Invalid input with duplicate numbers." << std::endl;
                return false;
            }
            seen.insert(row);
            seen.insert(col);
            seen.insert(blk);
        }
    }

    int count = count_solution_(0);
    if (count == 0)
    {
        std::cout << "Cannot solve, invalid input without any possible solution. " << std::endl;
        pass_valid = false;
    }
    else if (count > 1)
    {
        std::cout << "Multiple solutions. " << std::endl;
        std::string usr_input;
        std::cout << "Continue solve? (Y/y/yes/N/n/no)";
        std::cin >> usr_input;
        if (usr_input == "Y" || usr_input == "y" || usr_input == "yes")
            return true;
        else
            return false;
    }

    if (pass_valid)
        std::cout << "Puzzle pass validation." << std::endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time); // 计算时间差
    std::cout << "Validation takes " << duration.count() << " microseconds. " << std::endl;

    return pass_valid;
}

std::vector<int> Solver::str2num_(const std::string &puzzle)
{
    std::vector<int> nums;
    std::transform(puzzle.begin(), puzzle.end(), std::back_inserter(nums),
                   [](char c)
                   { return c - '0'; });
    return nums;
}

bool Solver::satisfyGivenPartialAssignment_(uint32_t todo_idx)
{
    move_best_todo_to_front_(todo_idx);
    Pos pos = cells_todo_[todo_idx];
    auto candidates = rows_[pos.row].bit_mask() & cols_[pos.col].bit_mask() & boxes_[pos.box].bit_mask();
    while (candidates)
    {
        uint32_t candidate = GetLowBit(candidates);
        // only count assignment as a guess if there's more than one candidate.
        if (candidates ^ candidate)
            num_guesses_++;

        // clear the candidate from available candidate sets for row, col, box
        // 该行、列、子块不能再填写candidate
        rows_[pos.row].bit_xor(candidate);
        cols_[pos.col].bit_xor(candidate);
        boxes_[pos.box].bit_xor(candidate);

        // 递归，若正确修改board，返回true
        if (todo_idx == num_todo_ || satisfyGivenPartialAssignment_(todo_idx + 1))
        {
            board_[pos.row][pos.col].set(1 + LowOrderBitIndex(candidate));
            return true;
        }

        // restore the candidate to available candidate sets for row, col, box
        // 若递归失败，取消candidate的占用，该数字可以填写
        rows_[pos.row].bit_or(candidate);
        cols_[pos.col].bit_or(candidate);
        boxes_[pos.box].bit_or(candidate);

        // 从candidates除去candidate

        candidates = ClearLowBit(candidates);
    }
    return false;
}

// 暴力搜索判断是否多解，不返回具体解法个数
int Solver::count_solution_(uint32_t todo_idx)
{
    if (solution_count_ > 1)
        return solution_count_;
    move_best_todo_to_front_(todo_idx);
    Pos pos = cells_todo_[todo_idx];
    auto candidates = rows_[pos.row].bit_mask() & cols_[pos.col].bit_mask() & boxes_[pos.box].bit_mask();
    while (candidates)
    {
        uint32_t candidate = GetLowBit(candidates);
        // only count assignment as a guess if there's more than one candidate.
        if (candidates ^ candidate)
            num_guesses_++;

        // clear the candidate from available candidate sets for row, col, box
        // 该行、列、子块不能再填写candidate
        rows_[pos.row].bit_xor(candidate);
        cols_[pos.col].bit_xor(candidate);
        boxes_[pos.box].bit_xor(candidate);

        // 递归，若正确修改board，返回true
        if (todo_idx == num_todo_ || count_solution_(todo_idx + 1))
        {
            // 递归到最后一个元素说明是可行解法
            if (todo_idx == num_todo_)
                solution_count_++;
        }

        // 取消占用
        rows_[pos.row].bit_or(candidate);
        cols_[pos.col].bit_or(candidate);
        boxes_[pos.box].bit_or(candidate);

        // 从candidates除去candidate
        candidates = ClearLowBit(candidates);
    }
    return solution_count_;
}

int Solver::num_candidates_(const Pos &pos)
{
    auto candidates = rows_[pos.row].bit_mask() & cols_[pos.col].bit_mask() & boxes_[pos.box].bit_mask();
    return NumBitsSet(candidates);
}

void Solver::move_best_todo_to_front_(uint32_t todo_index)
{
    std::sort(cells_todo_.begin() + todo_index,
              cells_todo_.end(),
              [&](const Pos &cell1, const Pos &cell2)
              {
                  return num_candidates_(cell1) < num_candidates_(cell2);
              });
}

bool Solver::solve()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    if (!satisfyGivenPartialAssignment_(0))
    {
        return false;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time); // 计算时间差
    duration_ = duration.count();
    return true;
}

int Solver::guesses()
{
    return num_guesses_;
}

double Solver::solve_time()
{
    return duration_;
}

void Solver::print_board()
{
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0)
        {
            std::cout << "-------------------" << std::endl;
        }
        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0)
            {

                std::cout << "|";
            }
            int val = board_[row][col].val();
            if (val == 0)
            {
                std::cout << " ";
            }
            else
            {
                std::cout << val;
            }
            if (col % 3 != 2)
            {
                std::cout << ' ';
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "-------------------" << std::endl;
}

void Solver::replace(std::string &puzzle, char oldc, char newc)
{
    std::replace(puzzle.begin(), puzzle.end(), oldc, newc);
}

bool Solver::valid_string(std::string puzzle)
{
    // 只判断是否是数字输入，不判断重复，无解的情况下提醒用户可能输入错误
    // 输入默认用0做占位符
    if (puzzle.size() != 81)
    {
        std::cout << "Invalid Input size " << puzzle.size() << ". Please input a puzzle string of size 81. " << std::endl;
        return false;
    }
    for (auto c : puzzle)
    {
        if (c < '0' || c > '9')
        {
            std::cout << "Invalid Input: " << puzzle << std::endl;
            std::cout << "Please input numbers. " << std::endl;
            return false;
        }
    }
    return true;
}
