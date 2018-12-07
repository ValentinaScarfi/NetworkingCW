#include "stdafx.h"
#include "SFML\Graphics\Text.hpp"
#include "ClientMatchmakeState.h"
#include "PlayState.h"
#include <iostream>

// The IP address for the server to listen on
#define SERVERIP "127.0.0.1"
//10.1.5.106
// The TCP port number for the server to listen on
#define SERVERPORT 5555

ClientMatchmakeState::ClientMatchmakeState(int playerSprite, GameDataRef data) : _data(data)
{
	tempSpriteID = playerSprite;
}


ClientMatchmakeState::~ClientMatchmakeState()
{
}

void ClientMatchmakeState::Init()
{
	//Title
	Title.setFont(this->_data->assets.GetFont("Default Font"));
	Title.setString("Connect to Server Lobby");
	Title.setCharacterSize(40);
	Title.setFillColor(sf::Color::White);
	Title.setPosition((SCREEN_WIDTH / 2) - (this->Title.getGlobalBounds().width / 2), 50.0f);

	//Error Message
	errorMessage.setFont(this->_data->assets.GetFont("Default Font"));
	errorMessage.setCharacterSize(30);

	//Button Connect
	this->_data->assets.LoadTexture("Connect Button", BUTTON_CONNECT);
	buttonConnect.setTexture(this->_data->assets.GetTexture("Connect Button"));
	buttonConnect.setPosition((SCREEN_WIDTH / 2) - (this->buttonConnect.getGlobalBounds().width / 2), 500.0f);

	//IP Caption
	IPCaption.setFont(this->_data->assets.GetFont("Default Font"));
	IPCaption.setString("IP Address");
	IPCaption.setCharacterSize(30);
	IPCaption.setFillColor(sf::Color::White);
	IPCaption.setPosition((SCREEN_WIDTH / 2) - (this->IPCaption.getGlobalBounds().width / 2), 200.0f);

	//ip Address handle
	IPText.setFont(this->_data->assets.GetFont("Default Font"));
	IPText.setString(ipString);
	IPText.setCharacterSize(25);
	IPText.setFillColor(sf::Color::Black);
	IPText.setPosition((SCREEN_WIDTH / 2) - (this->IPText.getGlobalBounds().width / 2), 250.0f);

	//TextBox IP
	textBoxIP = sf::RectangleShape(sf::Vector2f(450.f, 30.f));
	textBoxIP.setFillColor(sf::Color::White);
	textBoxIP.setPosition((SCREEN_WIDTH / 2) - (this->textBoxIP.getGlobalBounds().width / 2), 250.0f);


	//Port Caption
	portCaption.setFont(this->_data->assets.GetFont("Default Font"));
	portCaption.setString("Port");
	portCaption.setCharacterSize(30);
	portCaption.setFillColor(sf::Color::White);
	portCaption.setPosition((SCREEN_WIDTH / 2) - (this->portCaption.getGlobalBounds().width / 2), 350.0f);

	//Port Address handle
	portText.setFont(this->_data->assets.GetFont("Default Font"));
	portText.setString(portString);
	portText.setCharacterSize(25);
	portText.setFillColor(sf::Color::Black);
	portText.setPosition((SCREEN_WIDTH / 2) - (this->portText.getGlobalBounds().width / 2), 400.0f);

	//TextBox Port
	textBoxPort = sf::RectangleShape(sf::Vector2f(450.f, 30.f));
	textBoxPort.setFillColor(sf::Color::White);
	textBoxPort.setPosition((SCREEN_WIDTH / 2) - (this->textBoxPort.getGlobalBounds().width / 2), 400.0f);
}

void ClientMatchmakeState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (event.type == sf::Event::TextEntered && isIPFocus)
		{
			if (event.text.unicode < 128 )
			{
				if (!this->_data->input.isAxisKeyPressed(sf::Keyboard::BackSpace) && ipString.length() <= 20)
				{
					ipString += static_cast<char>(event.text.unicode);
				}
				else if (this->_data->input.isAxisKeyPressed(sf::Keyboard::BackSpace) && ipString.length() > 0)
				{
					ipString = ipString.substr(0, ipString.size() - 1);
				}
				
				IPText.setString(ipString);
				IPText.setPosition((SCREEN_WIDTH / 2) - (this->IPText.getGlobalBounds().width / 2), 250.0f);
			}
		}
		else if (event.type == sf::Event::TextEntered && isPortFocus)
		{
			if (event.text.unicode >= 48 && event.text.unicode <= 57 || event.text.unicode == 8)
			{
				if (!this->_data->input.isAxisKeyPressed(sf::Keyboard::BackSpace) && portString.length() <= 20)
				{
					portString += static_cast<char>(event.text.unicode);
				}
				else if (this->_data->input.isAxisKeyPressed(sf::Keyboard::BackSpace) && portString.length() > 0)
				{
					portString = portString.substr(0, portString.size() - 1);
				}
			}

			portText.setString(portString);
			portText.setPosition((SCREEN_WIDTH / 2) - (this->portText.getGlobalBounds().width / 2), 400.0f);
		}

		if (this->_data->input.isShapeClicked(this->textBoxIP, event, this->_data->window))
		{
			textBoxIP.setOutlineColor(sf::Color::Red);
			textBoxIP.setOutlineThickness(3.f);
			isIPFocus = true;
			isPortFocus = false;
			textBoxPort.setOutlineThickness(0.f);
		}

		if (this->_data->input.isShapeClicked(this->textBoxPort, event, this->_data->window))
		{
			textBoxPort.setOutlineColor(sf::Color::Red);
			textBoxPort.setOutlineThickness(3.f);
			isIPFocus = false;
			isPortFocus = true;
			textBoxIP.setOutlineThickness(0.f);
		}

		if (this->_data->input.isSpriteClicked(this->buttonConnect, event, this->_data->window))
		{
			if (portString.length() > 0)
			{
				int port = std::stoi(portString);

				status = socket.connect(ipString, port);
				if (status != sf::Socket::Done)
				{
					errorMessage.setString("Server not found!");
					errorMessage.setFillColor(sf::Color::Red);
					errorMessage.setPosition((SCREEN_WIDTH / 2) - (this->errorMessage.getGlobalBounds().width / 2), 600.0f);
				}
				else
				{
					Title.setString("Connected!");
					Title.setFillColor(sf::Color::Green);
					Title.setPosition((SCREEN_WIDTH / 2) - (this->Title.getGlobalBounds().width / 2), 50.0f);
					isInLobby = true;
				}
			}
		}
	}
}

void ClientMatchmakeState::Update(float dt)
{
	sf::Packet packet;
	sf::Packet packetS;

	std::string s;

	if (isInLobby)
	{
		sf::Socket::Status status = socket.receive(packet);

		if (status != sf::Socket::Done)
		{
			errorMessage.setString("Disconnected!");
			errorMessage.setFillColor(sf::Color::Red);
			errorMessage.setPosition((SCREEN_WIDTH / 2) - (this->errorMessage.getGlobalBounds().width / 2), 600.0f);

			Title.setString("Connect to Server Lobby");
			Title.setFillColor(sf::Color::White);
			Title.setPosition((SCREEN_WIDTH / 2) - (this->Title.getGlobalBounds().width / 2), 50.0f);
			packetCounter = 0;
			isInLobby = false;
		}
		else
		{
			packet >> clientID >> s >> opponentIp >> opponentPort >> myPort >> opponentSpriteID;
			if (s == "clientready")
			{
				socket.disconnect();
				this->_data->machine.ChangeState(StateRef(new PlayState(tempSpriteID, clientID, opponentIp, opponentPort, opponentSpriteID, myPort, _data)));
			}
			else
			{
				std::cout << clientID << s << packetCounter << opponentIp << opponentPort << opponentSpriteID << std::endl;
				packetS << clientID << s << packetCounter << tempSpriteID;
				socket.send(packetS);
				packetCounter++;
			}

		}
	}
}

void ClientMatchmakeState::Draw()
{
	this->_data->window.clear();

	if (!isInLobby)
	{
		this->_data->window.draw(Title);
		this->_data->window.draw(buttonConnect);
		this->_data->window.draw(errorMessage);

		this->_data->window.draw(IPCaption);
		this->_data->window.draw(textBoxIP);
		this->_data->window.draw(IPText);

		this->_data->window.draw(portCaption);
		this->_data->window.draw(textBoxPort);
		this->_data->window.draw(portText);
	}
	else
	{
		this->_data->window.draw(Title);
	}

	this->_data->window.display();
}
