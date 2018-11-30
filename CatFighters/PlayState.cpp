#include "stdafx.h"
#include "PlayState.h"
#include <iostream>

PlayState::PlayState(int playerSprite, int playerID, GameDataRef data) : _data(data)
{
	this->spriteID = playerSprite;
	this->playerID = playerID;
	std::cout << "\n" << this->playerID << std::endl;
	player = new Player(playerSprite);
}

void PlayState::Init()
{
	this->_data->assets.LoadTexture("Game Background", BACKGROUND_GAME);
	background.setTexture(this->_data->assets.GetTexture("Game Background"));

	int healthBarX = 50.f;
	if (playerID == 2)
	{
		healthBarX = 900;
	}
	//Border of health bar
	this->_data->assets.LoadTexture("Health Border", HEALTH_BORDER);
	healthBorder.setTexture(this->_data->assets.GetTexture("Health Border"));
	this->healthBorder.setScale(0.4f, 0.7f);
	this->healthBorder.setPosition(healthBarX, (50 - (this->healthBorder.getGlobalBounds().height / 2)));

	//health bar
	this->_data->assets.LoadTexture("Health Bar", HEALTH_BAR);
	healthBar.setTexture(this->_data->assets.GetTexture("Health Bar"));
	this->healthBar.setScale(0.4f, 0.7f);
	this->originalHealthScale = this->healthBar.getScale();
	this->healthBar.setPosition(healthBarX, (50 - (this->healthBar.getGlobalBounds().height / 2)));

	if (playerID == 2)
	{
		player->mySprite.loadSprite(true);
	}
	else 
	{
		player->mySprite.loadSprite();
	}
	
}

void PlayState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type || this->_data->input.isActionKeyPressed(event, sf::Keyboard::Escape))
		{
			this->_data->window.close();
		}

		if (this->_data->input.isActionKeyPressed(event, sf::Keyboard::H))
		{
			this->player->getDamage();
			healthBar.setScale(calculatePercentage(originalHealthScale.x, player->health), healthBar.getScale().y);
		}

	}
}

void PlayState::Update(float dt)
{
	player->mySprite.Animate();
	player->windowSize = this->_data->window.getView().getSize().x;

	if (this->_data->input.isAxisKeyPressed(sf::Keyboard::D))
	{
		this->player->moveRight(dt);
	}
	else if (this->_data->input.isAxisKeyPressed(sf::Keyboard::A))
	{
		this->player->moveLeft(dt);
	}
	else
	{
		this->player->velocity.x = 0.0f;
	}

	if (this->_data->input.isAxisKeyPressed(sf::Keyboard::Space) && this->player->canJump)
	{
		this->player->canJump = false;
		this->player->jump(dt);
		//this->player->mySprite.isJumping = true;
	}

	this->player->mySprite.activeSprite.sprite.move(this->player->velocity * dt);

	if (this->player->mySprite.activeSprite.sprite.getPosition().y < 400.0f)
	{
		this->player->velocity.y += GRAVITY * dt;
		this->player->mySprite.activeSprite.sprite.move(this->player->velocity * dt);
		//this->player->mySprite.isFalling = true;
		//this->player->mySprite.isJumping = false;
	}
	else if (this->player->mySprite.activeSprite.sprite.getPosition().y >= 400.0f)
	{
		this->player->mySprite.activeSprite.sprite.setPosition(this->player->mySprite.activeSprite.sprite.getPosition().x, 400.0f);
		this->player->velocity.y = 0.0f;
		this->player->canJump = true;
	}
	//else if (this->player->mySprite.activeSprite.sprite.getPosition().y == 400.0f)
	//{
	//	this->player->velocity.y = 0.0f;
	//	this->player->canJump = true;
	//	//this->player->mySprite.isFalling = false;
	//	//this->player->mySprite.isJumping = false;
	//}

	//Animation Machine
	if (this->player->velocity.y == 0.0f)
	{
		this->player->isFalling = false;
		this->player->isJumping = false;
		if (this->player->isFalling != this->player->mySprite.isFalling || this->player->isJumping != this->player->mySprite.isJumping)
		{
			this->player->mySprite.isFalling = false;
			this->player->mySprite.isJumping = false;
			this->player->mySprite.animationMachine();
		}
	}
	else if (this->player->velocity.y < 0.0f)
	{
		this->player->isFalling = false;
		this->player->isJumping = true;
		if (this->player->isFalling != this->player->mySprite.isFalling || this->player->isJumping != this->player->mySprite.isJumping)
		{
			this->player->mySprite.isFalling = false;
			this->player->mySprite.isJumping = true;
			this->player->mySprite.animationMachine();
		}
	}
	else if (this->player->velocity.y > 0.0f)
	{
		this->player->isFalling = true;
		this->player->isJumping = false;
		if (this->player->isFalling != this->player->mySprite.isFalling || this->player->isJumping != this->player->mySprite.isJumping)
		{
			this->player->mySprite.isFalling = true;
			this->player->mySprite.isJumping = false;
			this->player->mySprite.animationMachine();
		}
	}

	//std::cout << this->player->mySprite.activeSprite.sprite.getPosition().y << std::endl;

	//send and receive updates
}

void PlayState::Draw(float dt)
{
	this->_data->window.clear();

	switch (spriteID)
	{
	case 1:
		this->_data->window.clear(sf::Color::Green);
		break;
	case 2:
		this->_data->window.clear(sf::Color::Red);
		break;
	case 3:
		this->_data->window.clear(sf::Color::Yellow);
		break;
	}

	this->_data->window.draw(this->background);
	this->_data->window.draw(this->healthBorder);
	this->_data->window.draw(this->healthBar);
	player->mySprite.Draw(this->_data->window);

	this->_data->window.display();
}

float PlayState::calculatePercentage(float baseNumber, int percentage)
{
	return (baseNumber * percentage) / 100.0f;
}
