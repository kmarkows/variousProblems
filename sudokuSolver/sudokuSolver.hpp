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
    void checkIfPossibleAndInsert(uint8_t i, uint8_t j);

    bool isSudokuSolved{false};
    bool hasNumberBeenInsertedInLastIteration{false};
    bool isFirstIteration{true};
    uint8_t insertionPerOneWhileLoopCounter{0};
    std::array<std::array<uint8_t, sudokuSize>, sudokuSize> sudoku{};

public:
    SudokuSolver();
    void solve();
    void print();
};