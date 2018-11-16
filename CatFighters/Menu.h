#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

class Menu : public State
{
public:
	Menu( GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	sf::Clock clock;

	sf::Sprite background;
	sf::Sprite playButton;
};

