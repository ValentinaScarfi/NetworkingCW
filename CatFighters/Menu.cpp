#include "stdafx.h"
#include "Menu.h"
#include "SelectCharacterState.h"
#include <sstream>
#include <iostream>

Menu::Menu(GameDataRef data) : _data(data)
{
}

void Menu::Init()
{
	this->_data->assets.LoadTexture("Main Menu Background", BACKGROUND_MENU_PATH);
	background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
	
	this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_PATH);
	playButton.setTexture(this->_data->assets.GetTexture("Play Button"));

	this->playButton.setPosition((SCREEN_WIDTH / 2) - (this->playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->playButton.getGlobalBounds().height / 2));
}

void Menu::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (this->_data->input.isSpriteClicked(this->playButton, event, this->_data->window))
		{
			this->_data->machine.ChangeState(StateRef(new SelectCharacterState(_data)));
		}
	}
}

void Menu::Update(float dt)
{

}

void Menu::Draw()
{
	this->_data->window.clear();
	this->_data->window.draw(this->background);
	this->_data->window.draw(this->playButton);
	this->_data->window.display();
}
