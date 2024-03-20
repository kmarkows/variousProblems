#include "./sudokuSolver.hpp"

int main()
{
    SudokuSolver sudokuSolver{};
    sudokuSolver.print();
    sudokuSolver.solve();
    return 0;
}