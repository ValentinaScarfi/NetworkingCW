#include "stdafx.h"
#include "Game.h"
#include "Menu.h"
#include <iostream>

Game::Game(int width, int height, std::string title)
{
	_data->window.create(sf::VideoMode(width, height), title);
;	_data->machine.AddState(StateRef(new Menu(this->_data)));
	_data->window.setFramerateLimit(60);

	_data->assets.LoadFont("Default Font", FONT);
	_data->assets.LoadTexture("Generic Texture", GENERIC_TEXTURE);

	this->Run();
}

void Game::Run()
{
	float newTime, frameTime, interpolation;

	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->_data->window.isOpen())
	{
		this->_data->machine.ProcessStateChanges();

		newTime = this->_clock.getElapsedTime().asSeconds();
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

		interpolation = accumulator / dt;
		this->_data->machine.GetActiveState()->Draw(interpolation);
	}

}
