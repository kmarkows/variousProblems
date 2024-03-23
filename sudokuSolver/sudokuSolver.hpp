#include <iostream>
#include <fstream>
#include <stdint.h>
#include <cstdlib>
#include <array>
#include <string>

constexpr uint8_t sudokuSize = 9;

class SudokuSolver
{
private:
    void readUnsolvedSudokuFromFile();
    void saveSolvedSudokuToFile();
    bool solveRecurrsively(uint8_t startRow, uint8_t startCol);

    uint8_t getCellId(const uint8_t row, const uint8_t col);
    std::pair<uint8_t, uint8_t> getNextEmptyPosition(uint8_t row, uint8_t col);
    void setInitialConditions();

    std::array<std::array<uint8_t, sudokuSize>, sudokuSize> sudoku{};
    std::array<std::bitset<sudokuSize>, sudokuSize> rowsBits{0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::array<std::bitset<sudokuSize>, sudokuSize> columnsBits{0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::array<std::bitset<sudokuSize>, sudokuSize> cellsBits{0, 0, 0, 0, 0, 0, 0, 0, 0};

public:
    SudokuSolver();
    void solve();
    void print();
};