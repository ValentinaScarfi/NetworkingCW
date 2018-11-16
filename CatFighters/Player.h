#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(int playerSpriteID);
	~Player();

	int health = 100;

	void getDamage();

	
};

