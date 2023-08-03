# SudokuSolver

A simplest sudoku solver using brute force algorithm. Reference to [t-dillon](https://t-dillon.github.io/tdoku/) for algorithm and [this sudoku project](https://github.com/mayerui/sudoku) for GUI. 

## Build

Can be built for both `windows` and `linux`. 

```
mkdir build && cd build
cmake ..
make
```

Final executable will be placed in `./bin`

## Usage

Using -h/--help or just the executable to see usage.

```
Usage:
  sudoku_solver <puzzle> Or // solve puzzle directly
  sudoku_solver -g // use GUI to input puzzle
```

Where <puzzle> is a string of size 81, representing the row-major Sudoku puzzle to be solved and including numbers only. '0' or '.' is used as place holder. 

Use `-v` or `--version` option to see version info. 

## GUI guide

- **Move:** ASWD or HJKL ( VIM ) for ← ↓ ↑ →

- **Set number:** input [1-9] to set, 0 to clear

- **Quit:** Esc or q

- **Confirm:** Enter

## Example

### GUI:

```
./sudoku_solver -g
```

output:

```
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃   ┃ 9 ┃   ┃   ┃ 3 ┃   ┃ 7 ┃ 5 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃   ┃   ┃   ┃ 7 ┃ 9 ┃   ┃   ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 3 ┃   ┃ 4 ┃ 5 ┃   ┃ 2 ┃   ┃ 9 ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃   ┃ 7 ┃   ┃ 4 ┃   ┃ 5 ┃   ┃ 6 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃ 6 ┃   ┃   ┃   ┃   ┃   ┃ 4 ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 4 ┃   ┃ 1 ┃   ┃ 3 ┃   ┃ 9 ┃   ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃ 8 ┃   ┃ 2 ┃   ┃ 4 ┃ 7 ┃   ┃ 9 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃   ┃   ┃ 8 ┃ 1 ┃   ┃   ┃   ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 1 ┃ 4 ┃   ┃ 3 ┃   ┃   ┃ 2 ┃   ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━^━╋━━━╋━━━╋

Puzzle pass validation.
Validation takes 718 microseconds. 
Answer: 

╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 8 ┃ 2 ┃ 9 ┃ 1 ┃ 6 ┃ 3 ┃ 4 ┃ 7 ┃ 5 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 5 ┃ 1 ┃ 6 ┃ 4 ┃ 7 ┃ 9 ┃ 8 ┃ 3 ┃ 2 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 3 ┃ 7 ┃ 4 ┃ 5 ┃ 8 ┃ 2 ┃ 6 ┃ 9 ┃ 1 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 2 ┃ 3 ┃ 7 ┃ 9 ┃ 4 ┃ 1 ┃ 5 ┃ 8 ┃ 6 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 9 ┃ 6 ┃ 8 ┃ 7 ┃ 2 ┃ 5 ┃ 1 ┃ 4 ┃ 3 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 4 ┃ 5 ┃ 1 ┃ 6 ┃ 3 ┃ 8 ┃ 9 ┃ 2 ┃ 7 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 6 ┃ 8 ┃ 3 ┃ 2 ┃ 5 ┃ 4 ┃ 7 ┃ 1 ┃ 9 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 7 ┃ 9 ┃ 2 ┃ 8 ┃ 1 ┃ 6 ┃ 3 ┃ 5 ┃ 4 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 1 ┃ 4 ┃ 5 ┃ 3 ┃ 9 ┃ 7 ┃ 2 ┃ 6 ┃ 8 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋

Solve in 80 microseconds with 5 guesses.
```

### command:

```
./sudoku_solver 4...3.......6..8..........1....5..9..8....6...7.2........1.27..5.3....4.9........
# Or use 0 as place holder
# ./sudoku_solver 400030000000600800000000001000050090080000600070200000000102700503000040900000000
```

output:

```
Puzzle: 

╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 4 ┃   ┃   ┃   ┃ 3 ┃   ┃   ┃   ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃   ┃   ┃ 6 ┃   ┃   ┃ 8 ┃   ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃ 1 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃   ┃   ┃   ┃ 5 ┃   ┃   ┃ 9 ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃ 8 ┃   ┃   ┃   ┃   ┃ 6 ┃   ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃ 7 ┃   ┃ 2 ┃   ┃   ┃   ┃   ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃   ┃   ┃   ┃ 1 ┃   ┃ 2 ┃ 7 ┃   ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 5 ┃   ┃ 3 ┃   ┃   ┃   ┃   ┃ 4 ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 9 ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋

Puzzle pass validation.
Validation takes 12600 microseconds.
Answer:

╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 4 ┃ 6 ┃ 8 ┃ 9 ┃ 3 ┃ 1 ┃ 5 ┃ 2 ┃ 7 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 7 ┃ 5 ┃ 1 ┃ 6 ┃ 2 ┃ 4 ┃ 8 ┃ 3 ┃ 9 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 3 ┃ 9 ┃ 2 ┃ 5 ┃ 7 ┃ 8 ┃ 4 ┃ 6 ┃ 1 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 1 ┃ 3 ┃ 4 ┃ 7 ┃ 5 ┃ 6 ┃ 2 ┃ 9 ┃ 8 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 2 ┃ 8 ┃ 9 ┃ 4 ┃ 1 ┃ 3 ┃ 6 ┃ 7 ┃ 5 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 6 ┃ 7 ┃ 5 ┃ 2 ┃ 8 ┃ 9 ┃ 3 ┃ 1 ┃ 4 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 8 ┃ 4 ┃ 6 ┃ 1 ┃ 9 ┃ 2 ┃ 7 ┃ 5 ┃ 3 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 5 ┃ 1 ┃ 3 ┃ 8 ┃ 6 ┃ 7 ┃ 9 ┃ 4 ┃ 2 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋
┃ 9 ┃ 2 ┃ 7 ┃ 3 ┃ 4 ┃ 5 ┃ 1 ┃ 8 ┃ 6 ┃
╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋

Solve in 10403 microseconds with 1546 guesses.
```

## Features

- Check if **multiple solutions** or **no solution** exist using the same brute force algorithm
- Output **checking and solving time** and **guesses number** during solving
- **GUI input**
