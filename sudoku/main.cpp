#include <SFML/Graphics.hpp>
#include "sudoku_rendering.hpp"
#include "sudoku_board.hpp"
#include "game.hpp"

// switch to WinMain in release mode
int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 800)), "Sudoku");
    SudokuBoard board;
    SudokuRenderer renderer(window, board);
    SudokuGame game(window, board, renderer);
    renderer.game = &game;

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        // draw all elements
        game.runSudokuGame();
        window.display();
    }

    return 0;
}