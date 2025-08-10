#include <SFML/Graphics.hpp>
#include <optional>
#include "sudoku_rendering.hpp"
#include "sudoku_board.hpp"
#include "game.hpp"

int runGame() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 800)), "Sudoku");
    SudokuBoard board;
    SudokuRenderer renderer(window, board);
    SudokuGame game(window, board, renderer);
    renderer.game = &game;

    window.setFramerateLimit(60);
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

#ifdef _DEBUG
int main() { return runGame(); }
#else
#include <Windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) { return runGame(); }
#endif
