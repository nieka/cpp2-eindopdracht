#pragma once
#include <vector>
#include <string>
#include "ClientCommand.h"
#include "Player.h"
#include "Deck.h"
#include "RoundType.h"

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
	std::vector<std::shared_ptr<Card>> _tempBouwkaarten;
	int counter;
	RoundType _roudType;
	bool inRound;
	bool gotReward;
	bool abilityUsed;
	std::string currentKarakter = "";
};

