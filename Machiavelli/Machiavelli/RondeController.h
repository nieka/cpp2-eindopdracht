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
	void HandleGameCommands(const ClientCommand command, Controller& controller, GameController& gameController, Deck<std::shared_ptr<Card>> cardDeck);

	void startRound(Controller& controller, GameController& gameController, Deck<std::shared_ptr<Card>> cardDeck);

private:
	void printRoundInfo(Controller& controller, GameController& gameController);
	std::vector<std::string> _oproepVolgorde;
	std::vector<std::shared_ptr<Card>> _tempBouwkaarten;
	int counter;
	RoundType _lastType;
	RoundType _roundType;
	bool inRound;
	bool gotReward;
	bool abilityUsed;
	bool _firstTomaxBuildings;
	std::string currentKarakter = "";
	const int BUILDINGSNEEDEDTOWIN = 8;
	void resetKarakters(GameController & gcon);
	int _gebouwdeGebouwen = 0;
	void endOfRound(Controller & controller, GameController & gameController);
	void printstats(Controller & controller, GameController & gameController);
	void printkarakter(Controller & controller, GameController & gameController);
	void printplayers(Controller & controller, GameController & gameController);
};

