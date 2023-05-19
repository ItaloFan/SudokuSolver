#include <iostream>
#include <locale.h>
#include "SudokuSolverConfig.h"
#include "solver.h"
#include "scene.h"

// 用于输出间隔符
void dividing_line()
{
    std::cout << "------------------------------------------------------------" << std::endl;
}

void print_version()
{
    dividing_line();
    std::cout << "SudokuSolver " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
    std::cout << "  ( Commit ID: " << GIT_COMMIT_ID << " Commit Date: " << GIT_COMMIT_DATE << " )" << std::endl;
    std::cout << "Repository https://github.com/ItaloFan/SudokuSolver" << std::endl;
}

void print_help()
{
    dividing_line();
    std::cout << "Usage:\n "
              << "sudoku_solver.exe [<puzzle>] [<option>]\n";
    dividing_line();
    std::cout << "Where <puzzle> is a string of size 81, representing "
              << "the \nrow-major Sudoku puzzle to be solved and including numbers only. " << std::endl;
    std::cout << "'0' or '.' is used as a place holder. " << std::endl;
    dividing_line();
    std::cout << "Alternatively, add /g option to use GUI. \n";
    dividing_line();
}

int main(int argc, char const *argv[])
{
    // 处理输入
    if (argc == 1)
    {
        print_version();
        print_help();
        return 0;
    }
    else if (argc > 2 or std::string(argv[1]) == "-h" or std::string(argv[1]) == "--help")
    {
        print_help();
        return 0;
    }
    std::string puzzle = argv[1];
    if (puzzle == "/g")
    {
        Scene scene = Scene();
        scene.input();
        if (scene.confirm)
        {
            puzzle = scene.get_puzzle();
        }
        else
        {
            return 0;
        }
    }

    Solver solver;
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