#pragma once
#include "SFML\Network.hpp"
#include "Player.h"
#include <iostream>

class Server
{
public:
	Server(unsigned short myPort);
	~Server();

	void listenToPeer();
	void acceptPeer();
	void receiveOpponentData(sf::Packet packet);

private:

	sf::TcpListener listener;
	sf::TcpSocket clientPeer;
	unsigned short myPort;
};

