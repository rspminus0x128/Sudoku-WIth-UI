#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape rect;
    sf::Text text;
    sf::FloatRect btnBounds;
    bool wasPressedLastFrame = false;

public:
    Button(sf::Vector2f position, sf::Vector2f btnSize, unsigned int fontSize, sf::Font& font, const sf::String& label)
        : text(font, label, fontSize)
    {
        rect.setPosition(position);
        rect.setSize(btnSize);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = text.getLocalBounds();
        btnBounds = rect.getGlobalBounds();
        text.setOrigin(textBounds.getCenter());
        text.setPosition(btnBounds.getCenter());
    }

    void draw(sf::RenderWindow& window)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (btnBounds.contains((sf::Vector2f)mousePos))
        {
            rect.setFillColor(sf::Color(0, 100, 255, 255));
        }
        else
        {
            rect.setFillColor(sf::Color(0, 100, 255, 150));
        }
        window.draw(rect);
        window.draw(text);
    }

    bool isClicked(sf::RenderWindow& window)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        bool isOver = rect.getGlobalBounds().contains((sf::Vector2f)mousePos);
        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        bool clicked = false;
        // Register click only if mouse was pressed over button last frame and now released while still over button
        if (!isPressed && wasPressedLastFrame && isOver) {
            clicked = true;
        }
        wasPressedLastFrame = isPressed && isOver;
        return clicked;
    }
};