#pragma once
class SudokuBoard
{
public:
	int board[9][9] = { 0 };
	static constexpr int boardSize = 9;

	bool isMoveLegal(int row, int col, int num);

	enum Difficulty {
		Easy = 20,
		Medium = 30,
		Hard = 40
	};

	Difficulty difficulty;
	bool checkWin();
	void generatePuzzle();
	void clearBoard();
private:
	void fillDiagonalSubgrids();
	bool backtrack();
	void removeCells(Difficulty& difficulty);

};