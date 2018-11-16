#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerSheet.h"

class Player
{
public:
	Player(int playerSpriteID);
	~Player();

	int health = 100;
	float speed = 20.0f;

	void getDamage();

	PlayerSheet mySprite;	

	float windowSize;

	void moveLeft();
	void moveRight();

private:
	float thresholdBound = 100;
	
};

