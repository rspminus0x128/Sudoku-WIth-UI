#pragma once

#include <SFML/Graphics.hpp>
#include "sudoku_board.hpp"

class SudokuRenderer;

class SudokuGame
{
private:
	void loadFont(sf::Font& font);

public:
	sf::Font gameFont;
	bool inMenu;
	bool isPlaying;
	bool gameOver;

	SudokuGame(sf::RenderWindow& window, SudokuBoard& board, SudokuRenderer& renderer) : 
		window(window), renderer(renderer), board(board)
	{
		loadFont(gameFont);
		inMenu = true;
		isPlaying = false;
		gameOver = false;

	};

	sf::RenderWindow& window;
	SudokuRenderer& renderer;
	SudokuBoard& board;


	void runSudokuGame();
};


