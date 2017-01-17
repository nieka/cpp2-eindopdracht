#pragma once
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
	void skipPhase(Controller& controller, GameController& gameController, Deck<std::shared_ptr<IKarakter>>& karakterDeck);
};

