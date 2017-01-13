#pragma once
#include <fstream>
#include <istream>
#include <Iostream>
#include <string>
#include "ClientCommand.h"
#include "Deck.h"
#include "Card.h"
#include <string>
#include "Player.h"
#include "Socket.h"
#include "GameController.h"

class Controller
{
public:
	Controller();
	~Controller();

	void handleCommand(ClientCommand command);
	void printLine(const std::string value);

	std::vector<Player> getPlayers();
	
private:
	Deck deck;
	void createDeck(std::string filepath);
	
	bool started = false;

	//variable
	std::vector<Player> players;
	std::vector<Socket> playerSockets;
	GameController _gameController;
};

