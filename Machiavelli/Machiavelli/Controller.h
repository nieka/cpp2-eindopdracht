#pragma once
#include <fstream>
#include <istream>
#include <Iostream>
#include <string>
#include "ClientCommand.h"
#include "Deck.h"
#include "Card.h"
#include <string>

class Controller
{
public:
	Controller();
	~Controller();

	void handleCommand(ClientCommand command);
	
private:
	Deck<Card> deck;
	void createDeck(std::string filepath);
};

