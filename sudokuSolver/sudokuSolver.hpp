#include <iostream>
#include <fstream>
#include <stdint.h>
#include <cstdlib>
#include <array>
#include <string>
#include <set>

constexpr uint8_t sudokuSize = 9;

class SudokuSolver
{
private:
    void readUnsolvedSudokuFromFile();
    void saveSolvedSudokuToFile();

    std::array<std::array<uint8_t, sudokuSize>, sudokuSize> sudoku{};

public:
    SudokuSolver();
    void solve();
    void print();
};