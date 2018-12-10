#pragma once
#include <SFML/Graphics.hpp>
#include <thread> 
#include "State.h"
#include "Game.h"
#include "Player.h"
#include "Server.h"

class PlayState : public State
{
public:
	PlayState(int playerSprite, int playerID, std::string opponentIP, unsigned short oppPort, int oppSpriteID, unsigned short myPort, GameDataRef data);

	~PlayState() { delete player; delete playerOpponent; }

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw();

private:
	GameDataRef _data;

	sf::Text endGameText;

	Player *player;
	Player *playerOpponent;

	PlayerInfo tempOpponent;

	Connection conn;

	float currentTime;
	sf::Packet sPacket;
	sf::Packet rPacket;

	bool isWindowFocus = false;
	bool desync = false;
	bool gameEnded = false;

	int spriteID;
	int playerID;

	sf::Clock clock;

	sf::Sprite background;
	sf::Sprite healthBorder;
	sf::Sprite healthBar;

	sf::Sprite healthBorderOpponent;
	sf::Sprite healthBarOpponent;

	sf::Vector2f originalHealthScale;

	void updateAnimation(Player *player);
	void checkEndOfGame();
};