#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
	bool isShapeClicked(sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow &window);

	sf::Vector2i GetMousePosition(sf::RenderWindow &window);

	bool isActionKeyPressed(sf::Event event, sf::Keyboard::Key key);

	bool isAxisKeyPressed(sf::Keyboard::Key key);

private:
};

