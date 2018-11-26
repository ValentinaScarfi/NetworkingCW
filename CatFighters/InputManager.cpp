#include "stdafx.h"
#include "InputManager.h"
#include <iostream>


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

bool InputManager::isSpriteClicked(sf::Sprite object, sf::Event event, sf::RenderWindow & window)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (object.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			return true;
		}
	}

	return false;
}

bool InputManager::isShapeClicked(sf::RectangleShape object, sf::Event event, sf::RenderWindow & window)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (object.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			return true;
		}
	}

	return false;
}

bool InputManager::isActionKeyPressed(sf::Event event, sf::Keyboard::Key key)
{
	bool keyState = false;

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == key && !keyState)
		{
			return true;
			keyState = true;
		}
	}
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == key && keyState)
		{
			return false;
			keyState = false;
		}
	}
	return false;
}

bool InputManager::isAxisKeyPressed(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		return true;
	}

	return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow & window)
{
	return sf::Mouse::getPosition(window);
}


