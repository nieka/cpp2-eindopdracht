#pragma once
#include "ClientCommand.h"
#include "Deck.h"
class Controller
{
public:
	Controller();
	~Controller();

	void handleCommand(ClientCommand command);
	
private:
	Deck deck;
};

