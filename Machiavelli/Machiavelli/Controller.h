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
//#include "IKarakter.h"
//#include "DeckBuilder.h"

class Controller
{
public:
	Controller();
	~Controller();

	void handleCommand(ClientCommand command);
	void printLine(const std::string value);
	void createCardDeck();
	void createKarakterDeck();
	std::vector<Player> getPlayers();
	
private:
	bool started = false;

	//variable
	Deck<Card> _cardDeck;
	//Deck<IKarakter> _karakterDeck;
	std::vector<Player> players;
	std::vector<Socket> playerSockets;
	GameController _gameController;
	std::string _cardPath = "Bouwkaarten.csv";
	std::string _karakterPath = "karakterkaarten.csv";
};

