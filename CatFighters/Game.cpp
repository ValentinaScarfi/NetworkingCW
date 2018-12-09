#include "stdafx.h"
#include "Game.h"
#include "Menu.h"
#include <iostream>

Game::Game(int width, int height, std::string title)
{
	_data->window.create(sf::VideoMode(width, height), title);
;	_data->machine.ChangeState(StateRef(new Menu(this->_data)));
	_data->window.setFramerateLimit(60);
	_data->window.setKeyRepeatEnabled(false);

	//load default font
	_data->assets.LoadFont("Default Font", FONT);
	_data->assets.LoadTexture("Generic Texture", GENERIC_TEXTURE);

	this->Run();
}

void Game::Run()
{
	float newTime, frameTime;

	float currentTime = this->clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	//Main game loop
	while (this->_data->window.isOpen())
	{
		//process game state changes, calling init() accordingly
		this->_data->machine.ProcessStateChanges();

		newTime = this->clock.getElapsedTime().asSeconds();

		//how long it took between frames
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update(dt);
			
			accumulator -= dt;
		}

		this->_data->machine.GetActiveState()->Draw();
	}

}
