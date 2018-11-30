#include "stdafx.h"
#include "PlayerSheet.h"
#include <iostream>


PlayerSheet::PlayerSheet(int spriteID)
{
	switch (spriteID)
	{
	case 1:
	{
		//idle
		std::string idleTexture = "Simba Idle";
		asset.LoadTexture(idleTexture, PLAYER_SPRITE_SIMBA_IDLE);
		sf::Texture &idleText = asset.GetTexture(idleTexture);
		setSheetAttributes(idleText, idle, 10, 2, 2);

		//jump air
		std::string jumpAirTexture = "Simba JumpAir";
		asset.LoadTexture(jumpAirTexture, PLAYER_SPRITE_SIMBA_JUMPAIR);
		sf::Texture &jumpAirText = asset.GetTexture(jumpAirTexture);
		setSheetAttributes(jumpAirText, jumpAir, 10, 2, 2);

		//jump fall
		std::string jumpFallTexture = "Simba JumpFall";
		asset.LoadTexture(jumpFallTexture, PLAYER_SPRITE_SIMBA_JUMPFALL);
		sf::Texture &jumpFallText = asset.GetTexture(jumpFallTexture);
		setSheetAttributes(jumpFallText, jumpFall, 7, 2, 2);

		//attack

		
	}
		break;
	case 2:
	{
		//idle
		std::string idleTexture = "Pepper Idle";
		asset.LoadTexture(idleTexture, PLAYER_SPRITE_PEPPER_IDLE);
		sf::Texture &idleText = asset.GetTexture(idleTexture);
		setSheetAttributes(idleText, idle, 10, 2, 2);

		//jump air
		std::string jumpAirTexture = "Pepper JumpAir";
		asset.LoadTexture(jumpAirTexture, PLAYER_SPRITE_PEPPER_JUMPAIR);
		sf::Texture &jumpAirText = asset.GetTexture(jumpAirTexture);
		setSheetAttributes(jumpAirText, jumpAir, 10, 2, 2);

		//jump fall
		std::string jumpFallTexture = "Pepper JumpFall";
		asset.LoadTexture(jumpFallTexture, PLAYER_SPRITE_PEPPER_JUMPFALL);
		sf::Texture &jumpFallText = asset.GetTexture(jumpFallTexture);
		setSheetAttributes(jumpFallText, jumpFall, 8, 2, 2);

		//attack

	}
		break;
	case 3:
	{
		//idle
		std::string idleTexture = "Gigio Idle";
		asset.LoadTexture(idleTexture, PLAYER_SPRITE_GIGIO_IDLE);
		sf::Texture &idleText = asset.GetTexture(idleTexture);
		setSheetAttributes(idleText, idle, 10, 2, 2);

		//jump air

		//jump fall

		//attack

	}
		break;
	default:
		break;
	}

	activeSprite = idle;
}

PlayerSheet::~PlayerSheet()
{
}

void PlayerSheet::Draw(sf::RenderWindow &window)
{
	window.draw(activeSprite.sprite);
}

void PlayerSheet::Animate()
{
	animationAccumulator += 1;

	if (animationAccumulator >= activeSprite.animationSpeed)
	{
		xAnim++;

		if (xAnim == (activeSprite.columns + 1))
		{
			moveY = !moveY;
			activeSprite.spriteRect.left = 0.0f;
			xAnim = 1;
		}
		else
		{
			activeSprite.spriteRect.left = activeSprite.frameSize.x * (xAnim - 2);
		}

		switch (moveY)
		{
		case true:
			activeSprite.spriteRect.top = activeSprite.frameSize.y;
			break;
		case false:
			activeSprite.spriteRect.top = 0.0f;
			break;
		}
		
		activeSprite.sprite.setTextureRect(activeSprite.spriteRect);
		animationAccumulator = 0;
	}
}


void PlayerSheet::loadSprite(bool secondPlayer)
{
	if (secondPlayer)
	{
		activeSprite.sprite.setScale(-2.0f, 2.0f);
		activeSprite.sprite.setPosition(1000, 400);
	}
}

void PlayerSheet::animationMachine()
{

	if (!isJumping && !isFalling && !isAttacking)
	{
		idle.sprite.setScale(activeSprite.sprite.getScale());
		idle.sprite.setPosition(activeSprite.sprite.getPosition());
		activeSprite = idle;
		//std::cout << "Idle" << std::endl;
	}
	else if (isJumping && !isFalling && !isAttacking)
	{
		jumpAir.sprite.setScale(activeSprite.sprite.getScale());
		jumpAir.sprite.setPosition(activeSprite.sprite.getPosition().x, activeSprite.sprite.getPosition().y - 100);
		activeSprite = jumpAir;

		//std::cout << "JumpAir" << std::endl;

	}
	else if (!isJumping && isFalling && !isAttacking)
	{
		jumpFall.sprite.setScale(activeSprite.sprite.getScale());
		jumpFall.sprite.setPosition(activeSprite.sprite.getPosition());
		activeSprite = jumpFall;

		//std::cout << "jumpFall" << std::endl;
	}

	if (animationAccumulator != 0 || xAnim != 1 || moveY)
	{
		animationAccumulator = 0;
		xAnim = 1;
		moveY = false;
	}

}

void PlayerSheet::setSheetAttributes(sf::Texture & textureSheet, SpriteSheet &sheet, int animationSpeed, int columns, int rows)
{
	sheet.columns = columns;
	sheet.rows = rows;
	sheet.sprite.setTexture(textureSheet);
	sheet.frameSize = sf::Vector2i(textureSheet.getSize().x / columns, textureSheet.getSize().y / sheet.rows);
	sheet.spriteRect = sf::IntRect(0, 0, sheet.frameSize.x, sheet.frameSize.y);
	sheet.sprite.setTextureRect(sheet.spriteRect);

	sheet.sprite.setScale(2.0f, 2.0f);
	sheet.sprite.setPosition(170, 400);	

	sheet.sprite.setOrigin(sheet.sprite.getLocalBounds().width / 2, 0);

	sheet.animationSpeed = animationSpeed;
}
