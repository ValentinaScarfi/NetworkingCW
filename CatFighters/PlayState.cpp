#include "stdafx.h"
#include "PlayState.h"
#include <iostream>

PlayState::PlayState(int playerSprite, GameDataRef data) : _data(data)
{
	this->spriteID = playerSprite;
	player = new Player(playerSprite);
}

void PlayState::Init()
{
	//Border of health bar
	this->_data->assets.LoadTexture("Health Border", HEALTH_BORDER);
	healthBorder.setTexture(this->_data->assets.GetTexture("Health Border"));
	this->healthBorder.setScale(0.4f, 0.4f);
	this->healthBorder.setPosition(50, (50 - (this->healthBorder.getGlobalBounds().height / 2)));

	this->_data->assets.LoadTexture("Health Bar", HEALTH_BAR);
	healthBar.setTexture(this->_data->assets.GetTexture("Health Bar"));
	this->healthBar.setScale(0.4f, 0.4f);
	this->originalHealthScale = this->healthBar.getScale();
	this->healthBar.setPosition(50, (50 - (this->healthBar.getGlobalBounds().height / 2)));
}

void PlayState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (this->_data->input.isKeyPressed(event, sf::Keyboard::H))
		{
			this->player->getDamage();
			healthBar.setScale(calculatePercentage(originalHealthScale.x, player->health), healthBar.getScale().y);
		}
	}
}

void PlayState::Update(float dt)
{
	
}

void PlayState::Draw(float dt)
{
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

	this->_data->window.draw(this->healthBorder);
	this->_data->window.draw(this->healthBar);

	this->_data->window.display();
}

float PlayState::calculatePercentage(float baseNumber, int percentage)
{
	return (baseNumber * percentage) / 100.0f;
}
