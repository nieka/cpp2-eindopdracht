#pragma once
#include "ClientCommand.h"
#include "Player.h"

class GameController;
class Controller;
class ClientCommand;
class KarakterVedelingController
{
public:
	KarakterVedelingController();
	~KarakterVedelingController();

	void HandleGameCommands(ClientCommand command, Controller& controller, GameController& gameController);

};

