#include "solver.h"
#include "pos.h"
#include "common.h"
#include <algorithm>
#include <iostream>
#include <array>
#include <chrono>

Solver::Solver()
{
    clearAll();
    _num_guesses = 0;
}

Solver::Solver(std::string puzzle)
{
    _num_guesses = 0;
    init(puzzle);
}

void Solver::init(std::string puzzle)
{
    std::vector<int> nums = _str2num(puzzle);
    // fill 81 grid
    for (size_t i = 0; i < nums.size(); i++)
    {
        Pos pos = Pos(i);
        if (nums[i] > 0 && nums[i] <= 9)
        {
            _board[pos.row][pos.col].set(nums[i]);
            uint32_t value = 1u << (uint32_t)(nums[i] - 1);
            _rows[pos.row].bit_xor(value);
            _cols[pos.col].bit_xor(value);
            _boxes[pos.box].bit_xor(value);
        }
        else
        {
            _board[pos.row][pos.col].clear();
            _cells_todo.emplace_back(pos);
        }
    }
    _num_todo = _cells_todo.size() - 1;
}

std::vector<int> Solver::_str2num(const std::string &puzzle)
{
    std::vector<int> nums;
    std::transform(puzzle.begin(), puzzle.end(), std::back_inserter(nums),
                   [](char c)
                   { return c - '0'; });
    return nums;
}

bool Solver::_satisfyGivenPartialAssignment(uint32_t todo_idx)
{
    _move_best_todo_to_front(todo_idx);
    Pos pos = _cells_todo[todo_idx];
    auto candidates = _rows[pos.row].bit_mask() & _cols[pos.col].bit_mask() & _boxes[pos.box].bit_mask();
    while (candidates)
    {
        uint32_t candidate = GetLowBit(candidates);
        // only count assignment as a guess if there's more than one candidate.
        if (candidates ^ candidate)
            _num_guesses++;

        // clear the candidate from available candidate sets for row, col, box
        // 该行、列、子块不能再填写candidate
        _rows[pos.row].bit_xor(candidate);
        _cols[pos.col].bit_xor(candidate);
        _boxes[pos.box].bit_xor(candidate);

        // 递归，若正确修改board，返回true
        if (todo_idx == _num_todo || _satisfyGivenPartialAssignment(todo_idx + 1))
        {
            _board[pos.row][pos.col].set(1 + LowOrderBitIndex(candidate));
            return true;
        }

        // restore the candidate to available candidate sets for row, col, box
        // 若递归失败，取消candidate的占用，该数字可以填写
        _rows[pos.row].bit_or(candidate);
        _cols[pos.col].bit_or(candidate);
        _boxes[pos.box].bit_or(candidate);

        // 从candidates除去candidate

        candidates = ClearLowBit(candidates);
    }
    return false;
}

int Solver::_num_candidates(const Pos &pos)
{
    auto candidates = _rows[pos.row].bit_mask() & _cols[pos.col].bit_mask() & _boxes[pos.box].bit_mask();
    return NumBitsSet(candidates);
}

void Solver::_move_best_todo_to_front(uint32_t todo_index)
{
    std::sort(_cells_todo.begin() + todo_index,
              _cells_todo.end(),
              [&](const Pos &cell1, const Pos &cell2)
              {
                  return _num_candidates(cell1) < _num_candidates(cell2);
              });
}

bool Solver::full()
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (_board[row][col].empty())
            {
                std::cout << "Board is not full. " << std::endl;
                return false;
            }
        }
    }
    std::cout << "Board is full. " << std::endl;
    return true;
}

bool Solver::fill(const Pos &pos, int num)
{
    if (_board[pos.row][pos.col].empty())
    {
        if (!_rows[pos.row].exist(num) && !_cols[pos.col].exist(num) && !_boxes[pos.box].exist(num))
        {
            _board[pos.row][pos.col].set(num);
            return true;
        }
    }
    return false;
}

bool Solver::fill(int row, int col, int num)
{
    return fill(Pos(row, col), num);
}

void Solver::clear(const Pos &pos)
{
    _board[pos.row][pos.col].clear();
}
void Solver::clear(int row, int col)
{
    _board[row][col].clear();
}

void Solver::clearAll()
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            clear(row, col);
        }
    }
}

bool Solver::solve()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    if (_satisfyGivenPartialAssignment(0))
    {
        std::cout << "Solve Successfully. " << std::endl;
    }
    else
    {
        std::cout << "Solve Failed. You may input a invalid puzzle. " << std::endl;
        return false;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time); // 计算时间差
    _duration = duration.count();
    return true;
}

double Solver::solve_time()
{
    return _duration;
}

int Solver::guesses()
{
    return _num_guesses;
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
            int val = _board[row][col].val();
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

bool Solver::valid(std::string puzzle)
{
    // 只判断是否是数字输入，不判断重复，无解的情况下提醒用户可能输入错误
    // 输入默认用0做占位符
    if (puzzle.size() != 81)
    {
        std::cout << "Invalid Input. Please input a puzzle string of size 81. " << std::endl;
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
