#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerSheet.h"

class Player
{
public:
	Player(int playerSpriteID);

	~Player();

	int health = 100;
	float speed = 700.0f;
	int spriteID;

	void getDamage();

	PlayerSheet mySprite;

	float windowSize;

	void moveLeft(float dt);
	void moveRight(float dt);
	void jump(float dt);

	bool isFalling = false;
	bool isJumping = false;

	bool canJump = true;
	sf::Vector2f velocity;

private:
	float thresholdBound = 100;
	
	float jumpHeight = 150;

	float groundFloor;
};

