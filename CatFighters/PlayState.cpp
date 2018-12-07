#include "stdafx.h"
#include "PlayState.h"
#include <iostream>

PlayState::PlayState(int playerSprite, int playerID, std::string opponentIP, unsigned short oppPort, int oppSpriteID, unsigned short myPort, GameDataRef data) : _data(data), server(myPort), client(opponentIP, oppPort)
{
	clock.restart();
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

		client.connectToServerPeer();
		server.listenToPeer();
		server.acceptPeer();
	}
	else 
	{
		player->mySprite.loadSprite();
		playerOpponent->mySprite.loadSprite(true);

		server.listenToPeer();
		server.acceptPeer();
		client.connectToServerPeer();
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
				//playerOpponent->getDamage();
				this->player->isDamaging = true;
			}
		}

		//Jump
		if (this->_data->input.isActionKeyPressed(event, sf::Keyboard::Space) && !this->player->jumping)
		{
			this->player->jumping = true;
		}

		if (event.type == sf::Event::LostFocus)
		{
			isWindowFocus = false;
		}
		else
		{
			isWindowFocus = true;
		}
	}
}

void PlayState::Update(float dt)
{
	//input for movement
	if (this->_data->input.isAxisKeyPressed(sf::Keyboard::D) && isWindowFocus)
	{
		this->player->isMovingRight = true;
		this->player->isMovingLeft = false;
	}
	else if (this->_data->input.isAxisKeyPressed(sf::Keyboard::A) && isWindowFocus)
	{
		this->player->isMovingRight = false;
		this->player->isMovingLeft = true;
	}
	else
	{
		this->player->isMovingRight = false;
		this->player->isMovingLeft = false;
	}

	
	float currentTime = clock.getElapsedTime().asMilliseconds();

	//------send and receive updates client - server peer to peer
	this->player->updateMyInfo(this->player->myInfo, currentTime);

	client.sendPlayerData(sPacket, this->player->myInfo);
	server.receiveOpponentData(rPacket, tempOpponent);

	this->playerOpponent->retrieveMyNewInfo(tempOpponent, *player);

	if (tempOpponent.timestamp > this->player->myInfo.timestamp + 100 || tempOpponent.timestamp < this->player->myInfo.timestamp - 100)
	{
		std::cout << "Desynchronised" << std::endl;
	}

	//Animate and window boundaries
	player->mySprite.Animate();
	player->windowSize = this->_data->window.getView().getSize().x;
	this->player->updatePlayerState(dt);
	
	playerOpponent->updatePlayerState(dt);
	playerOpponent->mySprite.Animate();
	playerOpponent->windowSize = this->_data->window.getView().getSize().x;

	updateAnimation(this->playerOpponent);
	updateAnimation(this->player);

	this->player->updateHealthBar(healthBar, originalHealthScale);
	this->playerOpponent->updateHealthBar(healthBarOpponent, originalHealthScale);

	this->player->isDamaging = false;
}

void PlayState::Draw()
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
		playerCurrent->attackAccumulator++;
	}

	if (playerCurrent->attackAccumulator == 25)
	{
		playerCurrent->isAttacking = false;
		playerCurrent->attackAccumulator = 0;
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

