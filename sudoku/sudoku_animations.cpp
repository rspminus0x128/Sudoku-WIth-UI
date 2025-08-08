#include "sudoku_animations.hpp"
constexpr int cellSize = 60;
constexpr int gridSize = 9;

void blueBoxAnimation(sf::RenderWindow& window, sf::Vector2f& position)
{
	static int opacity = 0;
	sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));

	rect.setPosition(position);

	opacity = (opacity == 255) ? opacity : opacity + 1;
	rect.setFillColor(sf::Color((std::uint8_t(0), std::uint8_t(100), std::uint8_t(255), std::uint8_t(opacity))));

	window.draw(rect);
	
}