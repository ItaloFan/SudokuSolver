# SudokuSolver
A simplest sudoku solver using brute force algorithm. Reference to [t-dillon](https://t-dillon.github.io/tdoku/)
## Build
```
mkdir build && cd build
cmake ..
make
```
## Usage
Using -h option or just the executable to see usage.
```
Usage:
 ./sudoku_solver.exe <puzzle>
```
Where <puzzle> is a string of size 81, representing the row-major Sudoku puzzle to be solved and including numbers only.
## Example
command:
```
./sudoku_solver.exe 4...3.......6..8..........1....5..9..8....6...7.2........1.27..5.3....4.9........
```
output:
```
Puzzle:
-------------------
|4    |  3  |     |
|     |6    |8    |
|     |     |    1|
-------------------
|     |  5  |  9  |
|  8  |     |6    |
|  7  |2    |     |
-------------------
|     |1   2|7    |
|5   3|     |  4  |
|9    |     |     |
-------------------
Puzzle pass validation.
Validation takes 13060 microseconds.
Answer:
-------------------
|4 6 8|9 3 1|5 2 7|
|7 5 1|6 2 4|8 3 9|
|3 9 2|5 7 8|4 6 1|
-------------------
|1 3 4|7 5 6|2 9 8|
|2 8 9|4 1 3|6 7 5|
|6 7 5|2 8 9|3 1 4|
-------------------
|8 4 6|1 9 2|7 5 3|
|5 1 3|8 6 7|9 4 2|
|9 2 7|3 4 5|1 8 6|
-------------------
Solve in 10294 microseconds with 1546 guesses.
```
## Features
- Check if multiple solutions or no solution exist using the same brute force algorithm
- Output checking and solving time and guesses during solving
