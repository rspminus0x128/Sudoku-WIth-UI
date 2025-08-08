#include "sudoku_board.hpp"
#include <SFML/Graphics.hpp>
class SudokuGame;

class SudokuRenderer
{
private:
	sf::RenderWindow& window;
	SudokuBoard& board;
	int getChoice();
public:
	SudokuGame* game = nullptr;

	SudokuRenderer(sf::RenderWindow& window, SudokuBoard& board) : window(window), board(board) {};

	void drawGrid() const;
	void drawString(std::string& str, const int& fontSize, sf::Vector2f position) const;
	void drawNumbers() const;
	void handleClick();
	void drawBoard();
	void drawMenu(SudokuGame* game);
	void gameOver(SudokuGame* game);
	void drawWin(SudokuGame* game);

};