#include "GameController.h"
#include "Controller.h"
#include "ClientCommand.h"
#include "Player.h"

GameController::GameController()
{
	createCardDeck();
	createKarakterDeck();
}

GameController::~GameController()
{
}

void GameController::HandleGameCommands(ClientCommand command, Controller& controller)
{
	switch (_currentState)
	{
		case GameStates::KARAKTERVERDELING:
			karakterVerdelingController.HandleGameCommands(command, controller,*this);
		default:
			break;
	}
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

		for (int i = 0; i < 4; ++i) {
			_player1.AddBouwCard(_cardDeck.drawCard());
			_player2.AddBouwCard(_cardDeck.drawCard());
		}

		controller.printLine(_player1.get_name() + " is de koning en mag beginnen.");
		
		_currentState = GameStates::KARAKTERVERDELING;
		_currectPlayer = _player1;

		_kaartenOpTafel.push_back(_karakterDeck.drawCard());
		controller.printToPlayer("Het karakter: " + _kaartenOpTafel.at(0)->getName() +  " is op de afleg stapel gelegd!", _currectPlayer.get_name());
		controller.printToPlayer("Kies een van de karakters:", _currectPlayer.get_name());

		for (int i = 0; i < _karakterDeck.getDeck().size(); ++i) {
			controller.printToPlayer(i + ":" + _karakterDeck.getDeck().at(i)->getName(), _currectPlayer.get_name());
		}

}

Player & GameController::getCurrentPlayer()
{
	return _currectPlayer;
}


void GameController::karakterVerdeling(Controller& controller)
{
	
}

Deck<std::shared_ptr<IKarakter>> GameController::getKarakterCards() const
{
	return _karakterDeck;
}



void GameController::createCardDeck()
{
	std::ifstream file(_cardPath);
	while (file.good())
	{
		file >> _cardDeck;
	}

	file.close();
	_cardDeck.CreateCardDeck();
}

void GameController::createKarakterDeck()
{
	std::ifstream file(_karakterPath);
	while (file.good())
	{
		file >> _karakterDeck;
	}

	file.close();
	_karakterDeck.CreateIKarakterDeck();
}
