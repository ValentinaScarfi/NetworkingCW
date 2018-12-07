#include "stdafx.h"
#include "Server.h"


Server::Server(unsigned short myPort)
{
	this->myPort = myPort;
}


Server::~Server()
{
}

sf::Packet& operator >>(sf::Packet& packet, PlayerInfo& player)
{
	return packet >> player.health
		>> player.timestamp
		>> player.isAttacking >> player.isMovingLeft >> player.isMovingRight >> player.jumping
		>> player.isDamaging;
}

void Server::listenToPeer()
{
	sf::Socket::Status status = listener.listen(this->myPort);

	if (status != sf::Socket::Done)
	{
		std::cout << "Problems with the port" << std::endl;
	}
}

void Server::acceptPeer()
{
	sf::Socket::Status status = listener.accept(clientPeer);

	if (status != sf::Socket::Done)
	{
		std::cout << "Can't connect with peer client" << std::endl;
	}
	else
	{
		std::cout << "Client Connected" << std::endl;
	}
}

void Server::receiveOpponentData(sf::Packet packet, PlayerInfo &info)
{
	sf::Socket::Status status = clientPeer.receive(packet);

	if (status != sf::Socket::Done)
	{
		std::cout << "Can't receive data from client" << std::endl;
	}
	else
	{
		packet >> info;
	}
}

