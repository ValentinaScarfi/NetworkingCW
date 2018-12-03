#pragma once
#include "SFML\Network.hpp"
#include "Player.h"
#include <iostream>

class Client
{
public:
	Client(std::string opponentIP, unsigned short oppPort);
	~Client();

	sf::TcpSocket socket;
	void connectToServerPeer();

private:

	std::string oppIP;
	unsigned short oppPort;

};

