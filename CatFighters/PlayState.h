#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Player.h"


class PlayState : public State
{
public:
	PlayState(int playerSprite, int playerID, GameDataRef data);
	~PlayState() { delete player; }

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:

	float calculatePercentage(float baseNumber, int percentage);

	GameDataRef _data;

	Player *player;

	int spriteID;
	int playerID;

	sf::Clock clock;

	sf::Sprite background;
	sf::Sprite healthBorder;
	sf::Sprite healthBar;

	sf::Sprite playerSprite;

	sf::Vector2f originalHealthScale;
	sf::Vector2f originalHealthPos;


};