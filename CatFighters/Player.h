#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerSheet.h"

struct PlayerInfo
{
	float timestamp;
	int health;

	sf::Vector2f position;

	bool isAttacking;
	bool isMovingLeft;
	bool isMovingRight;
	bool jumping;
	bool isDamaging;
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
	void updateMyInfo(PlayerInfo &info, float timeStamp);
	void retrieveMyNewInfo(PlayerInfo &info, Player &opponent);
	void updatePlayerState(float dt);
	void updateHealthBar(sf::Sprite &health, sf::Vector2f originalHealthScale);

	void linearPrediction();

	PlayerSheet mySprite;
	PlayerInfo myInfo;

	float windowSize;
	int attackAccumulator = 0;

	void moveLeft(float dt);
	void moveRight(float dt);
	void jump(float dt);

	bool checkCollision(sf::Sprite boundsOpponent);

	bool isMovingLeft = false;
	bool isMovingRight = false;
	bool isDamaging = false;

	bool isFalling = false;
	bool isJumping = false;
	bool isAttacking = false;

	bool canAttack = true;
	bool jumping = false;

	sf::Vector2f velocity;

private:
	float thresholdBound = 100;
	
	float jumpHeight = 150;

	float groundFloor;

	float calculatePercentage(float baseNumber, int percentage);

	void storePreviousInfo(PlayerInfo &info);
	std::vector<sf::Vector2f> previousPosition;
	std::vector<float> previousTime;
};

