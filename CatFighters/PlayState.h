#pragma once
#include <SFML/Graphics.hpp>
#include <thread> 
#include "State.h"
#include "Game.h"
#include "Player.h"
#include "Server.h"
#include "Client.h"

class PlayState : public State
{
public:
	PlayState(int playerSprite, int playerID, std::string opponentIP, unsigned short oppPort, int oppSpriteID, unsigned short myPort, GameDataRef data);

	~PlayState() { delete player; delete playerOpponent; }

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	Player *player;
	Player *playerOpponent;

	Server server;
	Client client;


	int spriteID;
	int playerID;
	int attackAccumulator = 0;

	sf::Clock clock;

	sf::Sprite background;
	sf::Sprite healthBorder;
	sf::Sprite healthBar;

	sf::Sprite healthBorderOpponent;
	sf::Sprite healthBarOpponent;

	sf::Vector2f originalHealthScale;

	void updateAnimation(Player *player);
};