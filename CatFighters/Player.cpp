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

void Player::getDamage()
{
	this->health -= 1;
}

void Player::moveLeft(float dt)
{

	float left = thresholdBound;

	velocity.x = 0.0f;


	if (mySprite.activeSprite.getPosition().x <= left)
	{
		mySprite.activeSprite.setPosition(left, mySprite.activeSprite.getPosition().y);
	}
	else
	{
		velocity.x -= speed;
	}

	if (mySprite.activeSprite.getScale().x > 0)
	{
		mySprite.activeSprite.setScale(mySprite.activeSprite.getScale().x * -1.0f, mySprite.activeSprite.getScale().y);
	}
	
}

void Player::moveRight(float dt)
{
	float right = windowSize - thresholdBound;

	velocity.x = 0.0f;

	if (mySprite.activeSprite.getPosition().x >= right)
	{
		mySprite.activeSprite.setPosition(right, mySprite.activeSprite.getPosition().y);
	}
	else
	{
		velocity.x += speed;
	}

	if (mySprite.activeSprite.getScale().x < 0)
	{
		mySprite.activeSprite.setScale(mySprite.activeSprite.getScale().x * -1.0f, mySprite.activeSprite.getScale().y);
	}
}

void Player::jump(float dt)
{

	// square root (2.0f * gravity * jumpHeight)

	velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
	
	std::cout << velocity.y << "\n";
}
