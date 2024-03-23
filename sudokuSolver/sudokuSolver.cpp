#include "./sudokuSolver.hpp"

SudokuSolver::SudokuSolver()
{
    readUnsolvedSudokuFromFile();
}

void SudokuSolver::readUnsolvedSudokuFromFile()
{
    std::ifstream file;
    file.open("./unsolvedSudoku.txt");
    if (file.is_open())
    {
        std::string line{};
        uint8_t lineCounter = 0;
        while(std::getline(file, line))
        {
            uint8_t element = 0;
            uint8_t savedNumbersInLine = 0;
            while (savedNumbersInLine < sudokuSize)
            {
                if (line[element] != ' ')
                {
                    sudoku[lineCounter][savedNumbersInLine] = int(line[element]) - 48;
                    savedNumbersInLine++;
                }
                element++;
            }
            lineCounter++;
        }
    }
}

void SudokuSolver::saveSolvedSudokuToFile()
{
    std::ofstream file;
    file.open("./solvedSudoku.txt");
    for (const auto& line : sudoku)
    {
        for (const auto element : line)
        {
            file << (int)element << " ";
        }
        file << std::endl;
    }
}

void SudokuSolver::solve()
{
    saveSolvedSudokuToFile();
}

void SudokuSolver::print()
{
    for (const auto& row : sudoku)
    {
        for (const auto number : row)
        {
            std::cout << (int)number << " "; 
        }
        std::cout << std::endl;
    }
}