#include <iostream>
#include <locale.h>
#include "SudokuSolverConfig.h"
#include "solver.h"
#include "scene.h"
#include "easter_egg.h"

// 用于输出间隔符
void dividing_line()
{
    std::cout << "------------------------------------------------------------" << std::endl;
}

void print_version()
{
    std::cout << std::endl;
    if (PRE_RELEASE != "")
    {
        std::cout << "SudokuSolver " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << "-" << PRE_RELEASE << std::endl;
    }
    else
    {

        std::cout << "SudokuSolver " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
    }
    std::cout << "  ( Commit ID: " << GIT_COMMIT_ID << " Commit Date: " << GIT_COMMIT_DATE << " )" << std::endl;
    std::cout << std::endl;
    std::cout << "Repository https://github.com/ItaloFan/SudokuSolver" << std::endl;
}

void print_help()
{
    dividing_line();
    std::cout << "Usage: \n"
              << "sudoku_solver <puzzle> or \nsudoku_solver <option>\n";
    dividing_line();
    std::cout << "Where <puzzle> is row-major 81-char string. \n";
    std::cout << "'0' or '.' is used as a place holder. " << std::endl;
    dividing_line();
    std::cout << "Alternatively, use -g option to use GUI. \n";
    std::cout << "Use -gh to show gui guide. \n";
    dividing_line();
}

void gui_help()
{
    dividing_line();
    std::cout << "GUI Guide: \n";
    std::cout << "  Use keys to move cursor. \n";
    std::cout << "  UP: W/K\n";
    std::cout << "  DOWN: S/J\n";
    std::cout << "  LEFT: A/H\n";
    std::cout << "  RIGHT: D/L\n";
    std::cout << "  Other operations: \n";
    std::cout << "  Quit: Q/Esc\n";
    std::cout << "  Set value: 1-9\n";
    std::cout << "  Clear value: 0\n";
    std::cout << "  Confirm: Enter\n";
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
    else if (std::string(argv[1]) == "marx")
    {
        print_easter_egg();
        return 0;
    }
    std::string option = argv[1];
    if (option == "-gh")
    {
        gui_help();
        return 0;
    }
    else if (option == "-v" or option == "--version")
    {
        print_version();
        return 0;
    }
    std::string puzzle = argv[1];
    if (option == "-g")
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
    if (option != "-g")
    {

        std::cout << "Puzzle: " << std::endl;
        solver.print_board();
    }
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