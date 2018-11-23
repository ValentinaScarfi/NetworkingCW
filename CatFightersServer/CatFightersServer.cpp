// CatFightersServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <WinSock2.h>
#include "SFML\Network.hpp"

// The IP address for the server to listen on
#define SERVERIP "127.0.0.1"
//10.1.5.106
// The TCP port number for the server to listen on
#define SERVERPORT 5555



int main()

{
	printf("Server running\n");
	
	sf::IpAddress myIP;
	sf::SocketSelector selector;

	std::cout << "IP Address:" << myIP.getPublicAddress() << "\n";
	std::cout << "Port:" << SERVERPORT << "\n";

	std::vector<sf::TcpSocket*> clients;

	sf::TcpListener listener;

	if (listener.listen(SERVERPORT) != sf::Socket::Done)
	{
		printf("Error\n");
	}

	printf("Waiting for first connection...\n");

	while (clients.size() < 4)
	{
		sf::TcpSocket *socket = new sf::TcpSocket;
		if (listener.accept(*socket) != sf::Socket::Done)
		{
			printf("Error\n");
		}

		clients.push_back(socket);
		std::cout << clients.size() << std::endl;

		printf("Waiting for second connection...\n");
	}

	while (clients.size() > 3 )
	{
		std::cout << clients.size() << std::endl;
	}

    return 0;
}

