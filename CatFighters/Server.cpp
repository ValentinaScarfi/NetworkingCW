#include "stdafx.h"
#include "Server.h"


Server::Server(unsigned short myPort)
{
	this->myPort = myPort;
	listener.setBlocking(false);
	clientPeer.setBlocking(false);
}


Server::~Server()
{
}

void Server::listenToPeer()
{

}

void Server::acceptPeer()
{
	if (listener.listen(this->myPort) != sf::Socket::Done)
	{
		std::cout << "Problems with the port" << std::endl;
	}

	if (listener.accept(clientPeer) != sf::Socket::Done)
	{
		std::cout << "Can't connect with peer client" << std::endl;
	}
}
