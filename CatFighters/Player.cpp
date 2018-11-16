#include "stdafx.h"
#include "Player.h"
#include <iostream>

Player::Player(int playerSpriteID)
{
}


Player::~Player()
{
}

void Player::getDamage()
{
	this->health -= 1;
}
