#include "stdafx.h"
#include "Server.h"


Connection::Connection(unsigned short myPort, std::string opponentIP, unsigned short oppPort)
{
	this->myPort = myPort;
	this->oppIP = opponentIP;
	this->oppPort = oppPort;
}

Connection::~Connection()
{
}

sf::Packet& operator >>(sf::Packet& packet, PlayerInfo& player)
{
	return packet >> player.health
		>> player.timestamp
		>> player.position.x >> player.position.y
		>> player.isAttacking >> player.isMovingLeft >> player.isMovingRight >> player.jumping
		>> player.isDamaging;
}

sf::Packet& operator <<(sf::Packet& packet, const PlayerInfo& player)
{
	return packet << player.health
		<< player.timestamp
		<< player.position.x << player.position.y
		<< player.isAttacking << player.isMovingLeft << player.isMovingRight << player.jumping
		<< player.isDamaging;
}

void Connection::listenToPeer()
{
	sf::Socket::Status status = listener.listen(this->myPort);

	if (status != sf::Socket::Done)
	{
		std::cout << "Problems with the port" << std::endl;
	}
}

void Connection::acceptPeer()
{

	sf::Socket::Status status = listener.accept(clientPeer);

	if (status != sf::Socket::Done)
	{
		std::cout << "Can't connect with peer client" << std::endl;
		disconnected = true;
	}
	else
	{
		std::cout << "Client Connected" << std::endl;
		
	}
	
}

void Connection::receiveOpponentData(sf::Packet packet, PlayerInfo &info)
{
	sf::Socket::Status status = clientPeer.receive(packet);

	if (status != sf::Socket::Done)
	{
		std::cout << "Can't receive data from client" << std::endl;
		canReceive = false;
	}
	else
	{
		packet >> info;
		canReceive = true;
	}

}

void Connection::sendPlayerData(sf::Packet packet, PlayerInfo &info)
{
	packet << info;

	sf::Socket::Status status = clientPeer.send(packet);

	if (status != sf::Socket::Done)
	{
		std::cout << "Can't send data to server" << std::endl;
		canSend = false;
	}
	else
	{
		canSend = true;
	}
}

void Connection::connectToServerPeer()
{
	sf::Socket::Status status = clientPeer.connect(oppIP, oppPort);
	if (status != sf::Socket::Done)
	{
		std::cout << "Can't connect to peer server" << std::endl;
		disconnected = true;
	}
	else
	{
		std::cout << "Connected to server" << std::endl;

	}
}

