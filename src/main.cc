#include <iostream>
#include "solver.h"
#include "SudokuSolverConfig.h"

// 用于输出间隔符
void dividing_line()
{
    std::cout << "------------------------------------------------------------" << std::endl;
}

int main(int argc, char const *argv[])
{
    // 处理输入
    if (argc != 2 or std::string(argv[1]) == "-h" or std::string(argv[1]) == "--help")
    {
        dividing_line();
        std::cout << "SudokuSolver " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
        std::cout << "  ( Commit ID: " << GIT_COMMIT_ID << " Commit Date: " << GIT_COMMIT_DATE << " )" << std::endl;
        dividing_line();
        std::cout << "Usage:\n "
                  << "./sudoku_solver.exe <puzzle>"
                  << std::endl;
        dividing_line();
        std::cout << "Where <puzzle> is a string of size 81, representing "
                  << "the \nrow-major Sudoku puzzle to be solved and including numbers only. " << std::endl;
        std::cout << "'0' or '.' is used as a place holder. " << std::endl;
        return 0;
    }

    Solver solver;
    std::string puzzle = argv[1];
    Solver::replace(puzzle, '.', '0');
    if (!Solver::valid_string(puzzle))
    {
        return 0;
    }
    solver.init(puzzle);
    std::cout << "Puzzle: " << std::endl;
    solver.print_board();
    if (!solver.valid_puzzle())
    {
        return 0;
    }
    if (!solver.solve())
    {
        std::cout << "Cannot solve the Puzzle. " << std::endl;
        return 0;
    }
    std::cout << "Answer: " << std::endl;
    solver.print_board();
    std::cout << "Solve in " << solver.solve_time() << " microseconds with " << solver.guesses() << " guesses. " << std::endl;
    return 0;
}