// CatFightersServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML\Network.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <list>


// The IP address for the server to listen on
#define SERVERIP "127.0.0.1"
//10.1.5.106
// The TCP port number for the server to listen on
#define SERVERPORT 5555

struct Client
{
	int clientID;
	int spriteID;
	sf::TcpSocket socket;
	sf::Socket::Status status;
	std::string ip;
	unsigned short rPort;
	unsigned short lPort;
	bool toBeRemoved = false;
	float ping;
	bool readyToFight = false;
	std::string opponentIp;
	unsigned short opponentPort;
	int oppSpriteID;
};


int main()
{

	printf("Server running\n");
	
	sf::IpAddress myIP;
	sf::SocketSelector selector;

	std::size_t received;
	char dummy[1];

	std::cout << "IP Local:" << myIP.getLocalAddress() << "\n";
	std::cout << "IP Public:" << myIP.getPublicAddress() << "\n";
	std::cout << "Port:" << SERVERPORT << "\n";

	std::list<Client> clients;

	sf::TcpListener listener;
	int counter = -1;
	int currentCounter = 0;
	int clientCounterID = 0;
	std::string state;

	bool toMakeMatch = false;

	if (listener.listen(SERVERPORT) != sf::Socket::Done)
	{
		printf("Error\n");
	}

	selector.add(listener);

	while (true)
	{
		if (selector.wait())
		{
			if (selector.isReady(listener))
			{
				clients.emplace_back();

				if (listener.accept(clients.back().socket) != sf::Socket::Done)
				{
					clients.pop_back();
				}
				else
				{
					clientCounterID++;
					clients.back().clientID = clientCounterID;
					selector.add(clients.back().socket);
				}
			}
		}
		for (auto i = clients.begin(); i != clients.end();)
		{
			sf::Packet packet;

			if (i->readyToFight)
			{
				state = "clientready";
			}
			else
			{
				state = "clientping";
			}

			packet << i->clientID << state << i->opponentIp << i->opponentPort << i->rPort << i->oppSpriteID;

			std::string s;
			int pCounter;
			int tempID;

			sf::Clock clock;
			sf::Time t1;

			t1 = clock.restart();
			
			i->status = i->socket.send(packet);

			if (selector.isReady(i->socket))
			{
				if (i->status != sf::Socket::Done)
				{
					if (i->status == sf::Socket::Disconnected)
					{
						i->toBeRemoved = true;
					}
				}
				else
				{
					i->socket.receive(packet);
					packet >> tempID >> s >> pCounter >> i->spriteID >> i->ip;
					sf::Time t2 = clock.getElapsedTime();
					sf::Time totTime = t2 - t1;

					std::cout << tempID << s << pCounter << " with ping time (micro): " << totTime.asMicroseconds() << std::endl;

					i->ping = totTime.asMicroseconds();

				}
			}
			else
			{
				if (i->status == sf::Socket::Disconnected)
				{
					i->toBeRemoved = true;
				}
			}

			if (i->toBeRemoved)
			{
				selector.remove(i->socket);
				i = clients.erase(i);
			}
			else
			{
				i++;
			}
		}
		
		currentCounter = clients.size();
		if (currentCounter != counter)
		{
			int clientsCounter = 1;
			std::cout << "----------------------------------------------------------" << std::endl << std::endl;
			std::cout << "Clients connected: " << clients.size() << std::endl << std::endl;
			for (auto& c : clients)
			{
				//c.ip = c.socket.getRemoteAddress();
				c.lPort = c.socket.getLocalPort();
				c.rPort = c.socket.getRemotePort();

				std::cout << "Client "<< clientsCounter << " IP: " << c.ip << std::endl;
				std::cout << "Client " << clientsCounter << " remote port: " << c.rPort << std::endl;
				std::cout << "Client " << clientsCounter << " local port: " << c.lPort << std::endl << std::endl;
				clientsCounter++;
			}
			std::cout << "----------------------------------------------------------"<< std::endl;
			counter = currentCounter;

			if (currentCounter == 0)
			{
				clientCounterID = 0;
			}
		}

		if (currentCounter >= 2)
		{ 
			if (currentCounter == 2 && toMakeMatch)
			{
				auto startList = clients.begin();
				
				for (int i = 0; i < clients.size(); i+=2)
				{
					Client &c1 = *startList;
					std::advance(startList, 1);
					Client &c2 = *startList;

					if (c1.spriteID != 0 && c2.spriteID != 0)
					{
						c1.opponentIp = c2.ip;
						c2.opponentIp = c1.ip;

						c1.opponentPort = c2.rPort;
						c2.opponentPort = c1.rPort;

						c1.oppSpriteID = c2.spriteID;
						c2.oppSpriteID = c1.spriteID;

						c1.clientID = 1;
						c1.readyToFight = true;
						c2.clientID = 2;
						c2.readyToFight = true;

						if (i < clients.size() - 2)
							std::advance(startList, 1);
					}
				}
			}
			else if (currentCounter > 2)
			{

			}

			toMakeMatch = true;
		}
		else
		{
			toMakeMatch = false;
		}
	}

    return 0;
}
