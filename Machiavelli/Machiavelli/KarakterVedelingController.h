#pragma once
#include <algorithm>
#include <stdlib.h>     
#include <time.h>
#include "ClientCommand.h"
#include "Player.h"
#include "Deck.h"

class GameController;
class Controller;
class ClientCommand;
class KarakterVedelingController
{
public:
	KarakterVedelingController();
	~KarakterVedelingController();

	void HandleGameCommands(ClientCommand command, Controller& controller, GameController& gameController, Deck<std::shared_ptr<IKarakter>>& karakterDeck);
private :
	int step;
	bool deck = false;
	std::vector<std::shared_ptr<IKarakter>> cards;
	void skipPhase(Controller& controller, GameController& gameController, Deck<std::shared_ptr<IKarakter>>& karakterDeck);
};

