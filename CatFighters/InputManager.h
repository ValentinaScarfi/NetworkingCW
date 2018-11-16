#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
	sf::Vector2i GetMousePosition(sf::RenderWindow &window);

	bool isKeyPressed(sf::Event event, sf::Keyboard::Key key);

private:
};

