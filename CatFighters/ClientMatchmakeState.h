#pragma once
#include "SFML\Network.hpp"
#include "State.h"
#include "Game.h"
#include "Player.h"
#include "PlayState.h"

class ClientMatchmakeState : public State
{
public:
	ClientMatchmakeState(int playerSprite, GameDataRef data);
	~ClientMatchmakeState();

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	sf::TcpSocket socket;

	int tempSpriteID;

};

