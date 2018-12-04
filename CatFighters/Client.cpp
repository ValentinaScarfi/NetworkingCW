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
