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
    while(not isSudokuSolved)
    {
        std::cout << "hasNumberBeenInsertedInLastIteration: " << hasNumberBeenInsertedInLastIteration << std::endl;
        insertionPerOneWhileLoopCounter = 0;
        std::cout << "while loop begins" << std::endl;
        isSudokuSolved = true;
        for (uint8_t i = 0; i < sudokuSize; i++)
        {
            for (uint8_t j = 0; j < sudokuSize; j++)
            {
                if (sudoku[i][j] == 0)
                {
                    isSudokuSolved = false;
                    checkIfPossibleAndInsert(i, j);
                }
            }
        }
        isFirstIteration = false;
        std::cout << "insertionPerOneWhileLoopCounter: " << (int)insertionPerOneWhileLoopCounter << std::endl;
        hasNumberBeenInsertedInLastIteration = insertionPerOneWhileLoopCounter == 0 ? false : true;
        print();
    }
    std::cout << "hasNumberBeenInsertedInLastIteration: " << hasNumberBeenInsertedInLastIteration << std::endl;
    std::cout << "sudoku is solved" << std::endl;
    saveSolvedSudokuToFile();
}

void SudokuSolver::checkIfPossibleAndInsert(uint8_t i, uint8_t j)
{
    std::cout << "i: " << (int)i << " j: " << (int)j << std::endl;
    std::set possibleNumbers{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (uint8_t x = 0; x < sudokuSize; x++)
    {
        if (sudoku[x][j] != 0)
        {
            possibleNumbers.erase(sudoku[x][j]);
        }
    }

    for (uint8_t y = 0; y < sudokuSize; y++)
    {
        if (sudoku[i][y] != 0)
        {
            possibleNumbers.erase(sudoku[i][y]);
        }
    }

    int8_t subModuleStartX = i - i%3;
    int8_t subModuleStartY = j - j%3;

    for (uint8_t x = 0; x < 3; x++)
    {
        for (uint8_t y = 0; y < 3; y++)
        {
            possibleNumbers.erase(sudoku[subModuleStartX + x][subModuleStartY + y]);
        }
    }

    for (const auto element : possibleNumbers)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    if (possibleNumbers.size() == 1)
    {
        for (const auto element : possibleNumbers)
        {
            insertionPerOneWhileLoopCounter++;
            sudoku[i][j] = element;
        }
    }

    if (not hasNumberBeenInsertedInLastIteration and not isSudokuSolved and not isFirstIteration)
    {
        for (const auto element : possibleNumbers)
        {
            sudoku[i][j] = element;
        }
        insertionPerOneWhileLoopCounter++;
    }
}

void SudokuSolver::print()
{
    for (const auto& line : sudoku)
    {
        for (const auto number : line)
        {
            std::cout << (int)number << " "; 
        }
        std::cout << std::endl;
    }
}