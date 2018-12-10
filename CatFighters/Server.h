#pragma once
#include "SFML\Network.hpp"
#include "Player.h"
#include <iostream>

class Connection
{
public:
	Connection(unsigned short myPort, std::string opponentIP, unsigned short oppPort);
	~Connection();

	void listenToPeer();
	void acceptPeer();
	void connectToServerPeer();
	void receiveOpponentData(sf::Packet packet, PlayerInfo &info);
	void sendPlayerData(sf::Packet packet, PlayerInfo &info);

	bool disconnected = false;
	bool canSend = true;
	bool canReceive = true;

	sf::TcpSocket clientPeer;
	sf::SocketSelector selector;

private:

	sf::TcpListener listener;

	unsigned short myPort;
	std::string oppIP;
	unsigned short oppPort;
};

