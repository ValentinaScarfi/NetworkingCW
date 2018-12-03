#include "stdafx.h"
#include "PlayState.h"
#include <iostream>

PlayState::PlayState(int playerSprite, int playerID, std::string opponentIP, unsigned short oppPort, int oppSpriteID, unsigned short myPort, GameDataRef data) : _data(data), server(myPort), client(opponentIP, oppPort)
{
	this->spriteID = playerSprite;
	this->playerID = playerID;
	std::cout << "\n" << this->playerID << std::endl;
	player = new Player(playerSprite);
	playerOpponent = new Player(oppSpriteID);
}

void PlayState::Init()
{
	this->_data->assets.LoadTexture("Game Background", BACKGROUND_GAME);
	background.setTexture(this->_data->assets.GetTexture("Game Background"));

	int healthBarX = 50.f;
	int healthBarXOpp = 900.f;

	if (playerID == 2)
	{
		healthBarX = 900;
		healthBarXOpp = 50.f;
	}
	//Border of health bar
	this->_data->assets.LoadTexture("Health Border", HEALTH_BORDER);
	healthBorder.setTexture(this->_data->assets.GetTexture("Health Border"));
	this->healthBorder.setScale(0.4f, 0.7f);
	this->healthBorder.setPosition(healthBarX, (50 - (this->healthBorder.getGlobalBounds().height / 2)));

	//Border of opponent health bar
	this->healthBorderOpponent = healthBorder;
	this->healthBorderOpponent.setPosition(healthBarXOpp, (50 - (this->healthBorderOpponent.getGlobalBounds().height / 2)));

	//health bar
	this->_data->assets.LoadTexture("Health Bar", HEALTH_BAR);
	healthBar.setTexture(this->_data->assets.GetTexture("Health Bar"));
	this->healthBar.setScale(0.4f, 0.7f);
	this->originalHealthScale = this->healthBar.getScale();
	this->healthBar.setPosition(healthBarX, (50 - (this->healthBar.getGlobalBounds().height / 2)));

	//opponent health bar
	healthBarOpponent = healthBar;
	this->healthBarOpponent.setPosition(healthBarXOpp, (50 - (this->healthBarOpponent.getGlobalBounds().height / 2)));


	if (playerID == 2)
	{
		player->mySprite.loadSprite(true);
		playerOpponent->mySprite.loadSprite();

		//client.connectToServerPeer();
	}
	else 
	{
		player->mySprite.loadSprite();
		playerOpponent->mySprite.loadSprite(true);

		//server.acceptPeer();
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

		if (this->_data->input.isActionKeyPressed(event, sf::Keyboard::G))
		{
			this->player->isAttacking = true;
			if (this->player->checkCollision(playerOpponent->mySprite.activeSprite.sprite))
			{
				playerOpponent->getDamage(healthBarOpponent, originalHealthScale);
			}
		}
	}

}

void PlayState::Update(float dt)
{
	//if (playerID == 2)
	//{
	//	client.connectToServerPeer();
	//}
	//else
	//{
	//	server.acceptPeer();
	//}
	//Animate and window boundaries
	player->mySprite.Animate();
	player->windowSize = this->_data->window.getView().getSize().x;

	playerOpponent->mySprite.Animate();
	playerOpponent->windowSize = this->_data->window.getView().getSize().x;

	//input for movement
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

	//Jump
	if (this->_data->input.isAxisKeyPressed(sf::Keyboard::Space) && this->player->canJump)
	{
		this->player->canJump = false;
		this->player->jump(dt);
	}

	//move sprite to updated position
	this->player->mySprite.activeSprite.sprite.move(this->player->velocity * dt);

	//apply gravity
	if (this->player->mySprite.activeSprite.sprite.getPosition().y < 400.0f)
	{
		this->player->velocity.y += GRAVITY * dt;
		this->player->mySprite.activeSprite.sprite.move(this->player->velocity * dt);
	}
	else if (this->player->mySprite.activeSprite.sprite.getPosition().y >= 400.0f)
	{
		this->player->mySprite.activeSprite.sprite.setPosition(this->player->mySprite.activeSprite.sprite.getPosition().x, 400.0f);
		this->player->velocity.y = 0.0f;
		this->player->canJump = true;
	}

	updateAnimation(this->player);

	//------send and receive updates client - server peer to peer


}

void PlayState::Draw(float dt)
{
	this->_data->window.clear();

	this->_data->window.draw(this->background);
	this->_data->window.draw(this->healthBorder);
	this->_data->window.draw(this->healthBar);
	player->mySprite.Draw(this->_data->window);

	//opponent
	this->_data->window.draw(this->healthBorderOpponent);
	this->_data->window.draw(this->healthBarOpponent);
	playerOpponent->mySprite.Draw(this->_data->window);
	
	this->_data->window.display();
}

void PlayState::updateAnimation(Player *playerCurrent)
{

	if (playerCurrent->isAttacking)
	{
		attackAccumulator++;
	}

	if (attackAccumulator == 25)
	{
		playerCurrent->isAttacking = false;
		attackAccumulator = 0;
	}

	if (playerCurrent->isAttacking)
	{
		if (playerCurrent->isAttacking != playerCurrent->mySprite.isAttacking)
		{
			playerCurrent->mySprite.isAttacking = true;
			playerCurrent->mySprite.animationMachine();
		}
	}
	//Animation Machine for jump
	else if (playerCurrent->velocity.y == 0.0f && !playerCurrent->isAttacking)
	{
		playerCurrent->isFalling = false;
		playerCurrent->isJumping = false;
		if (playerCurrent->isFalling != playerCurrent->mySprite.isFalling || playerCurrent->isJumping != playerCurrent->mySprite.isJumping || playerCurrent->isAttacking != playerCurrent->mySprite.isAttacking)
		{
			playerCurrent->mySprite.isFalling = false;
			playerCurrent->mySprite.isJumping = false;
			playerCurrent->mySprite.isAttacking = false;
			playerCurrent->mySprite.animationMachine();
		}
	}
	else if (playerCurrent->velocity.y < 0.0f && !playerCurrent->isAttacking)
	{
		playerCurrent->isFalling = false;
		playerCurrent->isJumping = true;
		if (playerCurrent->isFalling != playerCurrent->mySprite.isFalling || playerCurrent->isJumping != playerCurrent->mySprite.isJumping || playerCurrent->isAttacking != playerCurrent->mySprite.isAttacking)
		{
			playerCurrent->mySprite.isFalling = false;
			playerCurrent->mySprite.isJumping = true;
			playerCurrent->mySprite.isAttacking = false;
			playerCurrent->mySprite.animationMachine();
		}
	}
	else if (playerCurrent->velocity.y > 0.0f && !playerCurrent->isAttacking)
	{
		playerCurrent->isFalling = true;
		playerCurrent->isJumping = false;
		if (playerCurrent->isFalling != playerCurrent->mySprite.isFalling || playerCurrent->isJumping != playerCurrent->mySprite.isJumping || playerCurrent->isAttacking != playerCurrent->mySprite.isAttacking)
		{
			playerCurrent->mySprite.isFalling = true;
			playerCurrent->mySprite.isJumping = false;
			playerCurrent->mySprite.isAttacking = false;
			playerCurrent->mySprite.animationMachine();
		}
	}
}

