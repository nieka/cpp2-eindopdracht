#include "GameController.h"
#include "Controller.h"
#include "ClientCommand.h"
#include "Player.h"
#include "ClientInfo.h"

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
	if (auto clientInfo = command.get_client_info().lock()) {
		if (clientInfo->get_player().get_name() != _currectPlayer.get_name()) {
			controller.printToPlayer("U bent nu nog niet aan de beurt", clientInfo->get_player().get_name());
		}
		else {
			switch (_currentState)
			{
			case GameStates::KARAKTERVERDELING:
				karakterVerdelingController.HandleGameCommands(command, controller, *this, _karakterDeck);
			default:
				break;
			}
		}
	}
}

void GameController::setupGame(Controller& controller)
{
		if (controller.getPlayers().at(0).getAge() < controller.getPlayers().at(1).getAge()) {
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
		controller.printToPlayer("Het karakter: " + _kaartenOpTafel.at(0)->getName() +  " is omgekerd op tafel gelegd!", _currectPlayer.get_name());
		controller.printToPlayer("Kies een van de karakters voor in je hand:", _currectPlayer.get_name());

		for (int i = 0; i < _karakterDeck.getDeck().size(); ++i) {
			controller.printToPlayer(std::to_string(i + 1) + ": " + _karakterDeck.getDeck().at(i)->getName(), _currectPlayer.get_name());
		}

}

Player & GameController::getCurrentPlayer()
{
	return _currectPlayer;
}


void GameController::karakterVerdeling(Controller& controller)
{
	
}

void GameController::toggleCurrentPlayer()
{
	if (_currectPlayer.get_name() == _player1.get_name()) {
		_player1 = _currectPlayer;
		_currectPlayer = _player2;
	}
	else {
		_player2 = _currectPlayer;
		_currectPlayer = _player1;
	}
}

Deck<std::shared_ptr<IKarakter>> GameController::getKarakterCards() const
{
	return _karakterDeck;
}

void GameController::legKaartOpTafel(std::shared_ptr<IKarakter> karakter)
{
	_kaartenOpTafel.push_back(karakter);
}

void GameController::setState(const GameStates state)
{
	_currentState = state;
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
