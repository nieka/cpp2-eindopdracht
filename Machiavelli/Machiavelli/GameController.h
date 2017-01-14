#pragma once
#include "Player.h"
#include "ClientCommand.h"

class Controller;
class ClientCommand;
class GameController
{
public:
	GameController();
	~GameController();

	void HandleGameCommands(ClientCommand command, Controller& controller);
	void setupGame(Controller& controller);
private:
	Player _player1;
	Player _player2;
	
};

