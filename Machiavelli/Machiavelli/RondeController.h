#pragma once
#include <vector>
#include <string>
#include "ClientCommand.h"
#include "Player.h"
#include "Deck.h"

class GameController;
class Controller;
class ClientCommand;
class RondeController
{
public:
	RondeController();
	~RondeController();
	void HandleGameCommands(ClientCommand command, Controller& controller, GameController& gameController, Deck<std::shared_ptr<Card>> cardDeck);

	void startRound(Controller& controller, GameController& gameController, Deck<std::shared_ptr<Card>> cardDeck);

private:
	void printRoundInfo(Controller& controller, GameController& gameController);
	std::vector<std::string> _oproepVolgorde;
	int counter;
	bool inRound;
	bool gotReward;
	bool abilityUsed;
	std::string currentKarakter = "";
};

