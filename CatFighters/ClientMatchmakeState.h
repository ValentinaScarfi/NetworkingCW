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

	//Main UI
	sf::Text Title;
	sf::Sprite buttonConnect;
	sf::Text errorMessage;

	//ip variables
	sf::Text IPCaption;
	sf::Text IPText;
	std::string ipString = "";
	sf::RectangleShape textBoxIP;

	//port variables
	sf::Text portCaption;
	sf::Text portText;
	std::string portString = "";
	sf::RectangleShape textBoxPort;

	
	bool isIPFocus = false;
	bool isPortFocus = false;

	bool isInLobby = false;

	sf::Socket::Status status;
	int packetCounter = 0;
	int clientID;
};

