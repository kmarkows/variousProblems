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
		while (std::getline(file, line))
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
	for (const auto &line : sudoku)
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
	setInitialConditions();
	bool isSudokuSolved = solveRecurrsively(0, 0);
	std::cout << "--- isSudokuSolved: " << (int)isSudokuSolved << " ---" << std::endl;
	print();
	saveSolvedSudokuToFile();
}

bool SudokuSolver::solveRecurrsively(uint8_t startRow, uint8_t startCol)
{
	std::pair<uint8_t, uint8_t> nextEmptyPosition{getNextEmptyPosition(startRow, startCol)};

	if (nextEmptyPosition.first == sudokuSize)
	{
		return true;
	}

	std::bitset<sudokuSize> currentPosBits = rowsBits[nextEmptyPosition.first] | columnsBits[nextEmptyPosition.second] |
											 cellsBits[getCellId(nextEmptyPosition.first, nextEmptyPosition.second)];

	if (currentPosBits.all())
	{
		return false;
	}

	for (uint8_t bitId = 0; bitId < sudokuSize; bitId++)
	{
		if (not currentPosBits[bitId])
		{
			sudoku[nextEmptyPosition.first][nextEmptyPosition.second] = bitId + 1;
			rowsBits[nextEmptyPosition.first].set(bitId);
			columnsBits[nextEmptyPosition.second].set(bitId);
			cellsBits[getCellId(nextEmptyPosition.first, nextEmptyPosition.second)].set(bitId);

			if (solveRecurrsively(nextEmptyPosition.first, nextEmptyPosition.second))
			{
				return true;
			}

			rowsBits[nextEmptyPosition.first].reset(bitId);
			columnsBits[nextEmptyPosition.second].reset(bitId);
			cellsBits[getCellId(nextEmptyPosition.first, nextEmptyPosition.second)].reset(bitId);
		}
	}

	sudoku[nextEmptyPosition.first][nextEmptyPosition.second] = 0;
	return false;
}

std::pair<uint8_t, uint8_t> SudokuSolver::getNextEmptyPosition(uint8_t row, uint8_t col)
{
	while (row != sudokuSize)
	{
		if (sudoku[row][col] == 0)
		{
			return {row, col};
		}
		row = row + (col + 1) / 9;
		col = (col + 1) % 9;
	}
	return {sudokuSize, 0};
}

uint8_t SudokuSolver::getCellId(const uint8_t row, const uint8_t col)
{
	return (row / 3) * 3 + col / 3;
}

void SudokuSolver::setInitialConditions()
{
	for (uint8_t row = 0; row < sudokuSize; row++)
	{
		for (uint8_t col = 0; col < sudokuSize; col++)
		{
			if (sudoku[row][col] != 0)
			{
				rowsBits[row].set(sudoku[row][col] - 1);
				columnsBits[col].set(sudoku[row][col] - 1);
				cellsBits[getCellId(row, col)].set(sudoku[row][col] - 1);
			}
		}
	}
}

void SudokuSolver::print()
{
	for (const auto &row : sudoku)
	{
		for (const auto number : row)
		{
			std::cout << (int)number << " ";
		}
		std::cout << std::endl;
	}
}