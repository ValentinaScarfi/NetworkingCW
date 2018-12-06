#include "stdafx.h"
#include "Player.h"
#include <iostream>

Player::Player(int playerSpriteID) : mySprite(playerSpriteID)
{
	groundFloor = 400.0f;
	this->spriteID = playerSpriteID;
	myInfo = PlayerInfo();
	myInfo.health = this->health;
	myInfo.opponentHealth = 100;

	myInfo.isAttacking = isAttacking;
	myInfo.isFalling = isFalling;
	myInfo.isJumping = isJumping;

	myInfo.scaleX = this->mySprite.activeSprite.sprite.getScale().x;
	myInfo.scaleY = this->mySprite.activeSprite.sprite.getScale().y;

	myInfo.accumultorAttack = attackAccumulator;

	myInfo.velocity = this->velocity;

	myInfo.playerPos.x = this->mySprite.activeSprite.sprite.getPosition().x;
	myInfo.playerPos.y = this->mySprite.activeSprite.sprite.getPosition().y;
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

void Player::updateMyInfo(PlayerInfo &info, Player &opponent)
{
	info.opponentHealth = opponent.health;

	info.isAttacking = this->isAttacking;
	info.isFalling = this->isFalling;
	info.isJumping = this->isJumping;

	info.scaleX = this->mySprite.activeSprite.sprite.getScale().x;
	info.scaleY = this->mySprite.activeSprite.sprite.getScale().y;

	info.accumultorAttack = this->attackAccumulator;

	info.velocity = this->velocity;

	info.playerPos.x = this->mySprite.activeSprite.sprite.getPosition().x;
	info.playerPos.y = this->mySprite.activeSprite.sprite.getPosition().y;
}

void Player::retrieveMyNewInfo(PlayerInfo &info, Player &opponent)
{
	opponent.health = info.opponentHealth;

	isAttacking = info.isAttacking;
	isFalling = info.isFalling;
	isJumping = info.isJumping;

	this->mySprite.activeSprite.sprite.setScale(info.scaleX, info.scaleY);

	attackAccumulator = info.accumultorAttack;

	velocity = info.velocity;

	this->mySprite.activeSprite.sprite.setPosition(info.playerPos);
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
