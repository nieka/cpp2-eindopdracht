#include "GameController.h"
#include "Controller.h"
#include "ClientCommand.h"
#include "Player.h"

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::HandleGameCommands(ClientCommand command, Controller& controller)
{
}

void GameController::setupGame(Controller& controller)
{
		if (controller.getPlayers().at(1).getAge() < controller.getPlayers().at(1).getAge()) {
			_player1 = controller.getPlayers().at(1);
			_player1.setKoning(true);
			_player2 = controller.getPlayers().at(0);
		}
		else {
			_player1 = controller.getPlayers().at(0);
			_player1.setKoning(true);
			_player2 = controller.getPlayers().at(1);
		}

		_player1.setGoudStukkken(2);
		_player2.setGoudStukkken(2);
}
