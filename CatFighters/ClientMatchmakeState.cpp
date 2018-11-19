#include "stdafx.h"
#include "ClientMatchmakeState.h"

// The IP address for the server to listen on
#define SERVERIP "127.0.0.1"
//10.1.5.106
// The TCP port number for the server to listen on
#define SERVERPORT 5555

ClientMatchmakeState::ClientMatchmakeState(int playerSprite, GameDataRef data) : _data(data)
{
	tempSpriteID = playerSprite;
}


ClientMatchmakeState::~ClientMatchmakeState()
{
}

void ClientMatchmakeState::Init()
{
}

void ClientMatchmakeState::HandleInput()
{
}

void ClientMatchmakeState::Update(float dt)
{

	sf::Socket::Status status = socket.connect(SERVERIP, SERVERPORT);
	if (status != sf::Socket::Done)
	{
		printf("Can't connect");
	}
	else
	{
		printf("Connected to lobby");
		this->_data->machine.AddState(StateRef(new PlayState(tempSpriteID, _data)), true);
	}
}

void ClientMatchmakeState::Draw(float dt)
{
}
