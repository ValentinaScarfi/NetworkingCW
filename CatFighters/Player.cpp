#include "stdafx.h"
#include "Player.h"
#include <iostream>

Player::Player(int playerSpriteID)
{
}


Player::~Player()
{
}

void Player::getDamage()
{
	this->health -= 1;
}

void Player::moveLeft()
{
	float left = thresholdBound;
	sf::Vector2f move;

	if (mySprite.activeSprite.getPosition().x <= left)
	{
		mySprite.activeSprite.setPosition(left, mySprite.activeSprite.getPosition().y);
	}
	else
	{
		move.x--;
	}

	mySprite.activeSprite.move(move * speed);

	if (mySprite.activeSprite.getScale().x > 0)
	{
		mySprite.activeSprite.setScale(mySprite.activeSprite.getScale().x * -1.0f, mySprite.activeSprite.getScale().y);
	}
	
}

void Player::moveRight()
{
	float right = windowSize - thresholdBound;
	sf::Vector2f move;

	if (mySprite.activeSprite.getPosition().x >= right)
	{
		mySprite.activeSprite.setPosition(right, mySprite.activeSprite.getPosition().y);
	}
	else
	{
		move.x++;
	}

	mySprite.activeSprite.move(move * speed);

	if (mySprite.activeSprite.getScale().x < 0)
	{
		mySprite.activeSprite.setScale(mySprite.activeSprite.getScale().x * -1.0f, mySprite.activeSprite.getScale().y);
	}
}
