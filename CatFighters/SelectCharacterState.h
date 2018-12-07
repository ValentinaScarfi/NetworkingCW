#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

class SelectCharacterState : public State
{
public:
	SelectCharacterState(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw();

private:
	GameDataRef _data;

	sf::Clock clock;

	sf::Sprite background;

	sf::Sprite simbaSelection;
	sf::Sprite pepperSelection;
	sf::Sprite gigioSelection;
};

