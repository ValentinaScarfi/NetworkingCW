#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerSheet.h"

struct PlayerInfo
{
	int health;
	int opponentHealth;

	bool isFalling;
	bool isJumping;
	bool isAttacking;

	int accumultorAttack;

	float scaleX;
	float scaleY;

	sf::Vector2f velocity;
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

	void getDamage();
	void updateMyInfo(PlayerInfo &info, Player &opponent);
	void retrieveMyNewInfo(PlayerInfo &info, Player &opponent);

	void updateHealthBar(sf::Sprite &health, sf::Vector2f originalHealthScale);

	PlayerSheet mySprite;
	PlayerInfo myInfo;

	float windowSize;
	int attackAccumulator = 0;

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

