#include "stdafx.h"
#include "SelectCharacterState.h"
#include "PlayState.h"
#include "ClientMatchmakeState.h"
#include <iostream>


SelectCharacterState::SelectCharacterState(GameDataRef data) : _data(data)
{
	std::cout << "Selection Screen";
}

void SelectCharacterState::Init()
{
	//Pepper Selection
	this->_data->assets.LoadTexture("Pepper Selection", PEPPER_SELECTION);
	pepperSelection.setTexture(this->_data->assets.GetTexture("Pepper Selection"));
	this->pepperSelection.setScale(0.4f, 0.4f);
	this->pepperSelection.setPosition((SCREEN_WIDTH / 2) - (this->pepperSelection.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->pepperSelection.getGlobalBounds().height / 2));

	//Simba Selection
	this->_data->assets.LoadTexture("Simba Selection", SIMBA_SELECTION);
	simbaSelection.setTexture(this->_data->assets.GetTexture("Simba Selection"));
	this->simbaSelection.setScale(0.4f, 0.4f);
	this->simbaSelection.setPosition(((SCREEN_WIDTH / 2) - (this->simbaSelection.getGlobalBounds().width / 2)) - 350, (SCREEN_HEIGHT / 2) - (this->simbaSelection.getGlobalBounds().height / 2));

	//Gigio Selection
	this->_data->assets.LoadTexture("Gigio Selection", GIGIO_SELECTION);
	gigioSelection.setTexture(this->_data->assets.GetTexture("Gigio Selection"));
	this->gigioSelection.setScale(0.4f, 0.4f);
	this->gigioSelection.setPosition(((SCREEN_WIDTH / 2) - (this->gigioSelection.getGlobalBounds().width / 2)) + 350, (SCREEN_HEIGHT / 2) - (this->gigioSelection.getGlobalBounds().height / 2));
}

void SelectCharacterState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (this->_data->input.isSpriteClicked(this->simbaSelection, event, this->_data->window))
		{
			//this->_data->machine.AddState(StateRef(new PlayState(1, 1, "localhost", 5555, 2, _data)), true);
			this->_data->machine.ChangeState(StateRef(new ClientMatchmakeState(1, _data)));
		}
		else if (this->_data->input.isSpriteClicked(this->pepperSelection, event, this->_data->window))
		{
			//this->_data->machine.AddState(StateRef(new PlayState(2, 1, "localhost", 5555, 2, _data)), true);
			this->_data->machine.ChangeState(StateRef(new ClientMatchmakeState(2, _data)));
		}
		else if (this->_data->input.isSpriteClicked(this->gigioSelection, event, this->_data->window))
		{
			//this->_data->machine.AddState(StateRef(new PlayState(3, 1, "localhost", 5555, 2, _data)), true);
			this->_data->machine.ChangeState(StateRef(new ClientMatchmakeState(3, _data)));
		}
	}
}

void SelectCharacterState::Update(float dt)
{
}

void SelectCharacterState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);
	this->_data->window.draw(this->pepperSelection);
	this->_data->window.draw(this->simbaSelection);
	this->_data->window.draw(this->gigioSelection);
	this->_data->window.display();
}

