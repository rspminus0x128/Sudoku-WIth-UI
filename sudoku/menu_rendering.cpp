#include "sudoku_rendering.hpp"
#include "game.hpp"
#include "button.hpp"

void SudokuRenderer::drawMenu(SudokuGame* game)
{
	sf::Vector2u windowSize = game->window.getSize();
	std::string levelMessage = "Select Level";
	drawString(levelMessage, 100, sf::Vector2f(windowSize.x / 2, 100));
	sf::Vector2f btnSize(500.f, 150.f);
	float btnOriginX = (windowSize.x - btnSize.x) / 2.f;
	float btnOriginY = (windowSize.y - btnSize.y) / 2.f + 50.f;
	constexpr float btnPadding = 10.f;

	// easy
	static Button buttonLevelEasy(sf::Vector2f(btnOriginX, btnOriginY - btnSize.y - btnPadding), btnSize, 50, game->gameFont, sf::String("Easy"));
	buttonLevelEasy.draw(game->window);
	if (buttonLevelEasy.isClicked(game->window))
	{
		game->inMenu = false;
		game->isPlaying = true;
		board.difficulty = SudokuBoard::Difficulty::Easy;
		board.generatePuzzle();
	}

	// medium
	static Button buttonLevelMedium(sf::Vector2f(btnOriginX, btnOriginY), btnSize, 50, game->gameFont, sf::String("Medium"));
	buttonLevelMedium.draw(game->window);
	if (buttonLevelMedium.isClicked(game->window))
	{
		game->inMenu = false;
		game->isPlaying = true;

		board.difficulty = SudokuBoard::Difficulty::Medium;
		board.generatePuzzle();
	}

	// hard
	static Button buttonLevelHard(sf::Vector2f(btnOriginX, btnOriginY + btnSize.y + btnPadding), btnSize, 50, game->gameFont, sf::String("Hard"));
	buttonLevelHard.draw(game->window);
	if (buttonLevelHard.isClicked(game->window))
	{
		game->inMenu = false;
		game->isPlaying = true;
		board.difficulty = SudokuBoard::Difficulty::Hard;
		board.generatePuzzle();
	}
}