#include "stdafx.h"
#include "Client.h"


Client::Client(std::string opponentIP, unsigned short oppPort)
{
	this->oppIP = opponentIP;
	this->oppPort = oppPort;
}


Client::~Client()
{
}

sf::Packet& operator <<(sf::Packet& packet, const PlayerInfo& player)
{
	return packet << player.health
		<< player.timestamp
		<< player.isAttacking << player.isMovingLeft << player.isMovingRight << player.jumping
		<< player.isDamaging;
}

void Client::connectToServerPeer()
{
	sf::Socket::Status status = socket.connect(oppIP, oppPort);
	if (status != sf::Socket::Done)
	{
		std::cout << "Can't connect to peer server" << std::endl;
	}
	else 
	{
		std::cout << "Connected to server" << std::endl;
	}
}

void Client::sendPlayerData(sf::Packet packet, PlayerInfo &info)
{
	packet << info;

	sf::Socket::Status status = socket.send(packet);

	if (status != sf::Socket::Done)
	{
		std::cout << "Can't send data to server" << std::endl;
	}
}
