#include "stdafx.h"
#include "Player.h"
#include <iostream>

Player::Player(int playerSpriteID) : mySprite(playerSpriteID)
{
	groundFloor = 400.0f;
	this->spriteID = playerSpriteID;
}


Player::~Player()
{
}


float Player::calculatePercentage(float baseNumber, int percentage)
{
	return (baseNumber * percentage) / 100.0f;
}

void Player::getDamage(sf::Sprite &health, sf::Vector2f originalHealthScale)
{
	if (this->health > 0)
	{
		this->health -= 1;
		health.setScale(calculatePercentage(originalHealthScale.x, this->health), health.getScale().y);
	}
}

void Player::updateMyInfo()
{
	this->myInfo.health = this->health;
	this->myInfo.playerPos = this->mySprite.activeSprite.sprite.getPosition();
}

void Player::retrieveMyNewInfo()
{
	this->health = this->myInfo.health;
	this->mySprite.activeSprite.sprite.setPosition(this->myInfo.playerPos);
}

void Player::moveLeft(float dt)
{

	float left = thresholdBound;

	velocity.x = 0.0f;


	if (mySprite.activeSprite.sprite.getPosition().x <= left)
	{
		mySprite.activeSprite.sprite.setPosition(left, mySprite.activeSprite.sprite.getPosition().y);
	}
	else
	{
		velocity.x -= speed;
	}

	if (mySprite.activeSprite.sprite.getScale().x > 0)
	{
		mySprite.activeSprite.sprite.setScale(mySprite.activeSprite.sprite.getScale().x * -1.0f, mySprite.activeSprite.sprite.getScale().y);
	}
	
}

void Player::moveRight(float dt)
{
	float right = windowSize - thresholdBound;

	velocity.x = 0.0f;

	if (mySprite.activeSprite.sprite.getPosition().x >= right)
	{
		mySprite.activeSprite.sprite.setPosition(right, mySprite.activeSprite.sprite.getPosition().y);
	}
	else
	{
		velocity.x += speed;
	}

	if (mySprite.activeSprite.sprite.getScale().x < 0)
	{
		mySprite.activeSprite.sprite.setScale(mySprite.activeSprite.sprite.getScale().x * -1.0f, mySprite.activeSprite.sprite.getScale().y);
	}
}

void Player::jump(float dt)
{

	// formula -> square root (2.0f * gravity * jumpHeight)
	velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
}

bool Player::checkCollision(sf::Sprite boundsOpponent)
{
	if (this->mySprite.activeSprite.sprite.getGlobalBounds().intersects(boundsOpponent.getGlobalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
