#include "stdafx.h"
#include "PlayerSheet.h"
#include <iostream>


PlayerSheet::PlayerSheet()
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

		switch (xAnim)
		{
		case 1: 
			playerIdleSource.left = 0.0f;
			break;
		case 2:
			playerIdleSource.left = frameSize.x;
			break;
		case 3:
			playerIdleSource.left = frameSize.x * 2;
			break;
		case 4:
			moveY = !moveY;
			playerIdleSource.left = 0.0f;
			xAnim = 1;
			break;
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

void PlayerSheet::loadSprite(int columns, int rows)
{
	//player sprite
	std::string textureName = "Simba Idle";
	asset.LoadTexture(textureName, PLAYER_SPRITE_SIMBA_IDLE);
	sf::Texture &current = asset.GetTexture(textureName);
	idle.setTexture(current);
	frameSize = sf::Vector2i(current.getSize().x / columns, current.getSize().y / rows);
	playerIdleSource = sf::IntRect(0, 0, frameSize.x, frameSize.y);
	idle.setTextureRect(playerIdleSource);
	idle.setScale(2.0f, 2.0f);
	idle.setPosition(170, 400);
	idle.setOrigin(idle.getLocalBounds().width / 2, 0);

	activeSprite = idle;
}
