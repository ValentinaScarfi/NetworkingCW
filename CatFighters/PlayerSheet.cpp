#include "stdafx.h"
#include "PlayerSheet.h"
#include <iostream>


PlayerSheet::PlayerSheet(int spriteID)
{
	
}


PlayerSheet::~PlayerSheet()
{
}

void PlayerSheet::Draw(sf::RenderWindow &window)
{
	window.draw(activeSprite);
}

void PlayerSheet::Animate(float dt, int columns, int rows)
{
	animationAccumulator += 1;

	if (animationAccumulator >= 10)
	{
		xAnim++;

		if (xAnim == (columns + 1))
		{
			moveY = !moveY;
			playerIdleSource.left = 0.0f;
			xAnim = 1;
		}
		else
		{
			playerIdleSource.left = frameSize.x * (xAnim - 2);
		}

		switch (moveY)
		{
		case true:
			playerIdleSource.top = frameSize.y;
			break;
		case false:
			playerIdleSource.top = 0.0f;
			break;
		}
		
		activeSprite.setTextureRect(playerIdleSource);
		animationAccumulator = 0;
	}

	
}

void PlayerSheet::loadSprite(int columns, int rows, bool secondPlayer)
{

	this->columns = columns;
	this->rows = rows;

	//player sprite
	std::string textureName = "Simba Idle";
	asset.LoadTexture(textureName, PLAYER_SPRITE_SIMBA_IDLE);
	sf::Texture &current = asset.GetTexture(textureName);
	idle.setTexture(current);
	frameSize = sf::Vector2i(current.getSize().x / columns, current.getSize().y / rows);
	playerIdleSource = sf::IntRect(0, 0, frameSize.x, frameSize.y);
	idle.setTextureRect(playerIdleSource);
	if (secondPlayer)
	{
		idle.setScale(-2.0f, 2.0f);
		idle.setPosition(1000, 400);
	}
	else
	{
		idle.setScale(2.0f, 2.0f);
		idle.setPosition(170, 400);
	}

	idle.setOrigin(idle.getLocalBounds().width / 2, 0);

	activeSprite = idle;
}
