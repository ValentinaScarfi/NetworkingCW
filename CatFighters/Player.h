#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerSheet.h"

struct PlayerInfo
{
	int playerID;
	int spriteID;
	int health;
	sf::Vector2f playerPos;
};

class Player
{
public:
	Player(int playerSpriteID);

	~Player();

	int health = 100;
	float speed = 700.0f;
	int spriteID;

	void getDamage(sf::Sprite &health, sf::Vector2f originalHealthScale);

	PlayerSheet mySprite;

	float windowSize;

	void moveLeft(float dt);
	void moveRight(float dt);
	void jump(float dt);

	bool checkCollision(sf::Sprite boundsOpponent);

	bool isFalling = false;
	bool isJumping = false;
	bool isAttacking = false;
	bool canAttack = true;
	bool canJump = true;

	sf::Vector2f velocity;

private:
	float thresholdBound = 100;
	
	float jumpHeight = 150;

	float groundFloor;

	float calculatePercentage(float baseNumber, int percentage);
};

