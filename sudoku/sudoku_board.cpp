#include "sudoku_board.hpp"
#include "sudoku_rendering.hpp"

bool SudokuBoard::checkWin()
{
	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			if (board[i][j] == 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

#include <random>
#include <vector>
#include <iostream>


bool SudokuBoard::isMoveLegal(int row, int col, int num)
{
	int startRow = (row / 3) * 3;
	int startCol = (col / 3) * 3;

	for (int i = 0; i < boardSize; ++i)
	{
		// check row
		if (board[row][i] == num && i != col)
		{
			return 0;
		}
		// check column
		if (board[i][col] == num && i != row)
		{
			return 0;
		}
	}
	// check cell
	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			if (board[startRow + r][startCol + c] == num &&
				startRow + r != row && startCol + c != col)
			{
				return 0;
			}
		}
	}
	return 1;
}

void SudokuBoard::fillDiagonalSubgrids()
{
	std::random_device rd;
	std::mt19937 num(rd());

	for (int i = 0; i <= 6; i += 3)
	{
		std::vector<int> pool = { 1,2,3,4,5,6,7,8,9 };
		std::shuffle(pool.begin(), pool.end(), num);

		for (int r = 0; r < 3; ++r)
		{
			for (int c = 0; c < 3; ++c)
			{
				int value = pool.back();
				pool.pop_back();
				board[i + r][i + c] = value;
			}
		}
	}
}

bool SudokuBoard::backtrack()
{
	if (checkWin()) return true;
	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			if (board[i][j] == 0)
			{
				for (int value = 1; value <= boardSize; ++value)
				{
					board[i][j] = value;
					if (isMoveLegal(i, j, value))
					{
						if (backtrack()) return true;
					}
					board[i][j] = 0;
				}
				return false;
			}
		}
	}
	return false;
}

void SudokuBoard::removeCells(Difficulty& difficulty)
{
	std::random_device rd;
	int count = difficulty;
	while (count > 0)
	{
		std::mt19937 num(rd());

		int randomRow = num() % 9;
		int randomCol = num() % 9;
		if (board[randomRow][randomCol] != 0)
		{
			board[randomRow][randomCol] = 0;
		}
		else continue;

		count--;
		
	}
}

void SudokuBoard::clearBoard()
{
	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			board[i][j] = 0;
		}
	}
}

void SudokuBoard::generatePuzzle()
{
	// fill diagonal boxes
	fillDiagonalSubgrids();
	// fill the rest
	backtrack();
	removeCells(difficulty);
}

