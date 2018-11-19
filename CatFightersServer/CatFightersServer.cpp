// CatFightersServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "SFML\Network.hpp"

// The IP address for the server to listen on
#define SERVERIP "127.0.0.1"
//10.1.5.106
// The TCP port number for the server to listen on
#define SERVERPORT 5555



int main()
{
	sf::TcpListener listener;
	if (listener.listen(SERVERPORT) != sf::Socket::Done)
	{
		printf("Error\n");
	}
	else
	{
	}

	printf("Waiting... for connection\n");

	sf::TcpSocket client;

	if (listener.accept(client) != sf::Socket::Done)
	{
		printf("Error\n");
	}

	while (true)
	{
		printf("Connected");
	}

    return 0;
}

