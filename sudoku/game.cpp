#include "game.hpp"
#include "utils.hpp"
#include <iostream>
#include "sudoku_rendering.hpp"

void SudokuGame::loadFont(sf::Font& font)
{
	if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf"))
	{
		std::cerr << "Failed to load font 'arial.ttf'. File may be missing";
		return;
	}
}

void SudokuGame::runSudokuGame() 
{

	if (inMenu)
	{
		renderer.drawMenu(this);
	}
	if (isPlaying)
	{
		renderer.drawBoard();
	}
	if (board.checkWin())
	{
		renderer.drawWin(this);
	}
	if (gameOver)
	{
		renderer.gameOver(this);
	}
}