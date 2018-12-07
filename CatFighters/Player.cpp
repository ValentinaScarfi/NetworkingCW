#include "stdafx.h"
#include "Player.h"
#include <iostream>

Player::Player(int playerSpriteID) : mySprite(playerSpriteID)
{
	groundFloor = 400.0f;
	this->spriteID = playerSpriteID;
	myInfo = PlayerInfo();
	myInfo.health = this->health;

	myInfo.isAttacking = isAttacking;

	myInfo.isMovingLeft = isMovingLeft;
	myInfo.isMovingRight = isMovingRight;
	myInfo.jumping = jumping;
	myInfo.isDamaging = isDamaging;
}


Player::~Player()
{
}

float Player::calculatePercentage(float baseNumber, int percentage)
{
	return (baseNumber * percentage) / 100.0f;
}

void Player::getDamage()
{
	if (this->health > 0)
	{
		this->health -= 1;
	}
}

void Player::updateMyInfo(PlayerInfo &info, float timeStamp)
{
	info.health = this->health;
	
	info.timestamp = timeStamp;

	info.isAttacking = this->isAttacking;

	info.isMovingLeft = this->isMovingLeft;
	info.isMovingRight = this->isMovingRight;
	info.jumping = this->jumping;
	info.isDamaging = this->isDamaging;
}

void Player::retrieveMyNewInfo(PlayerInfo &info, Player &opponent)
{
	this->health = info.health;

	isAttacking = info.isAttacking;

	this->isMovingLeft = info.isMovingLeft;
	this->isMovingRight = info.isMovingRight;
	this->jumping = info.jumping;
	this->isDamaging = info.isDamaging;

	if (info.isDamaging)
	{
		opponent.getDamage();
	}
}

void Player::updatePlayerState(float dt)
{
	if (isMovingLeft)
	{
		moveLeft(dt);
	}
	else if (isMovingRight)
	{
		moveRight(dt);
	}
	else 
	{
		this->velocity.x = 0.0f;
	}

	if (jumping)
	{
		this->jump(dt);
	}

	//move sprite to updated position
	this->mySprite.activeSprite.sprite.move(this->velocity * dt);

	//apply gravity
	if (this->mySprite.activeSprite.sprite.getPosition().y < 400.0f)
	{
		this->velocity.y += GRAVITY * dt;
		this->mySprite.activeSprite.sprite.move(this->velocity * dt);
		this->jumping = false;
	}
	else if (this->mySprite.activeSprite.sprite.getPosition().y >= 400.0f)
	{
		this->mySprite.activeSprite.sprite.setPosition(this->mySprite.activeSprite.sprite.getPosition().x, 400.0f);
		this->velocity.y = 0.0f;
		this->jumping = false;
	}
}

void Player::updateHealthBar(sf::Sprite &health, sf::Vector2f originalHealthScale)
{
	health.setScale(calculatePercentage(originalHealthScale.x, this->health), health.getScale().y);
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
