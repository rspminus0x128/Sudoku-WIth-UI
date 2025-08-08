#include "sudoku_rendering.hpp"
#include "sudoku_animations.hpp"
#include <iostream>
#include "sudoku_board.hpp"
#include "game.hpp"
#include "button.hpp"

static bool awaitingInput = 0;

constexpr int cellSize = 60;
constexpr int gridSize = 9;

void SudokuRenderer::SudokuRenderer::drawGrid() const {

	float thickness = 1.f;
    sf::Vector2u windowSize = window.getSize();
    float originX = (windowSize.x - (cellSize * gridSize)) / 2.f;
    float originY = (windowSize.y - (cellSize * gridSize)) / 2.f;

    for (int i = 0; i <= gridSize; ++i)
    {
        thickness = (i % 3 == 0) ? 4.f : 1.f;

        // vertical lines
        sf::RectangleShape vRect(sf::Vector2f(thickness, cellSize * gridSize));
        vRect.setPosition(sf::Vector2f((i * cellSize) + originX, originY));
        window.draw(vRect);

        // horizontal lines
        sf::RectangleShape hRect(sf::Vector2f(cellSize * gridSize, thickness));
        hRect.setPosition(sf::Vector2f(originX, (i * cellSize) + originY));
        window.draw(hRect);
    }
}

void SudokuRenderer::drawString(std::string& str, const int& fontSize, sf::Vector2f position) const 
{
    sf::Text text(game->gameFont, str, fontSize);
    text.setFillColor(sf::Color::White);
    text.setPosition(position);
    text.setOutlineColor(sf::Color::Red);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.getCenter());

    window.draw(text);
}

void SudokuRenderer::drawNumbers() const {
    sf::Vector2u windowSize = window.getSize();
    float originX = (windowSize.x - (cellSize * gridSize)) / 2.f;
    float originY = (windowSize.y - (cellSize * gridSize)) / 2.f;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (board.board[i][j] == 0) continue;

            constexpr int fontSize = 50;
            sf::Vector2f position;
            position.x = originX + j * cellSize + (cellSize / 2.f);
            position.y = originY + i * cellSize + (cellSize / 2.f);

            std::string strNum = std::to_string(board.board[i][j]);
            drawString(strNum, fontSize, position);
        }
    }
}

int SudokuRenderer::getChoice()
{
    sf::Keyboard::Key keys[9] = {  sf::Keyboard::Key::Num1,
                                    sf::Keyboard::Key::Num2, 
                                    sf::Keyboard::Key::Num3, 
                                    sf::Keyboard::Key::Num4, 
                                    sf::Keyboard::Key::Num5, 
                                    sf::Keyboard::Key::Num6, 
                                    sf::Keyboard::Key::Num7,
                                    sf::Keyboard::Key::Num8, 
                                    sf::Keyboard::Key::Num9 };

    for (int i = 1; i < 10; ++i)
    {
        if (sf::Keyboard::isKeyPressed(keys[i - 1]))
        {
            return i;
        }
    }

    return 0;
}

void SudokuRenderer::handleClick() {
    static int row, col;
    // get grid origins
    sf::Vector2u windowSize = window.getSize();
    float originX = (windowSize.x - (cellSize * gridSize)) / 2.f;
    float originY = (windowSize.y - (cellSize * gridSize)) / 2.f;

    if (!awaitingInput)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            // checking hitbox
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            // which hitbox?
            col = (mousePosition.x - originX) / cellSize;
            row = (mousePosition.y - originY) / cellSize;
            // check if click in in the grid
            if (row >= 0 && row < gridSize && col >= 0 && col < gridSize)
            {
                // get input on next call
                awaitingInput = 1;
            }
        }
    }
    if (awaitingInput)
    {
        if (board.board[row][col] != 0)
        {
            awaitingInput = 0;
            return;
        }

        // draw blue 'input' box
        sf::RectangleShape box(sf::Vector2f(cellSize, cellSize));
        box.setPosition(sf::Vector2f(col * cellSize + originX, row * cellSize + originY));
        box.setFillColor(sf::Color(0, 100, 255));
        window.draw(box);

        // get the choice
        int choice = getChoice();
        if (choice)
        {
            // if invalid move
            if (!board.isMoveLegal(row, col, choice))
            {
                box.setFillColor(sf::Color(255, 0, 0));
                window.draw(box);
                
                game->isPlaying = false;
                game->gameOver = true;
                
                return;
            }
            board.board[row][col] = choice;
            awaitingInput = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            awaitingInput = 0;
        }
    }
}

void SudokuRenderer::gameOver(SudokuGame* game)
{

    std::string gameOverMsg = "Game Over!";
    sf::Vector2u windowSize = game->window.getSize();

    drawString(gameOverMsg, 100, sf::Vector2f(windowSize.x / 2.f, 100));
    sf::Vector2f btnSize(500.f, 150.f);
    float btnOriginX = (windowSize.x - btnSize.x) / 2.f;
    float btnOriginY = (windowSize.y - btnSize.y) / 2.f + 50.f;

    static Button tryAgainBtn(sf::Vector2f(btnOriginX, btnOriginY), btnSize, 50, game->gameFont, sf::String("Try Again"));
    tryAgainBtn.draw(game->window);
    game->gameOver = true;
    game->isPlaying = false;
    if (tryAgainBtn.isClicked(game->window))
    {
        game->inMenu = true;
        game->gameOver = false;
        game->isPlaying = false;
        awaitingInput = false;
        game->board.clearBoard();
    }
}

void SudokuRenderer::drawWin(SudokuGame* game)
{
    std::string gameOverMsg = "You Win!";
    sf::Vector2u windowSize = game->window.getSize();

    drawString(gameOverMsg, 100, sf::Vector2f(windowSize.x / 2.f, 100));
    sf::Vector2f btnSize(500.f, 150.f);
    float btnOriginX = (windowSize.x - btnSize.x) / 2.f;
    float btnOriginY = (windowSize.y - btnSize.y) / 2.f + 50.f;

    static Button mainMenuBtn(sf::Vector2f(btnOriginX, btnOriginY), btnSize, 50, game->gameFont, sf::String("Main Menu"));
    mainMenuBtn.draw(game->window);
    game->gameOver = false;
    game->isPlaying = false;
    if (mainMenuBtn.isClicked(game->window))
    {
        game->inMenu = true;
        game->gameOver = false;
        game->isPlaying = false;
        awaitingInput = false;
        game->board.clearBoard();
    }

}

void SudokuRenderer::drawBoard()
{
    handleClick();
    drawGrid();
    drawNumbers();
}

