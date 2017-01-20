#include "GameController.h"
#include "Controller.h"
#include "ClientCommand.h"
#include "Player.h"
#include "ClientInfo.h"

GameController::GameController()
{
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
				_karakterVerdelingController.HandleGameCommands(command, controller, *this, _karakterDeck);
				break;
			case GameStates::RONDEN:
				_rondeController.HandleGameCommands(command, controller, *this, _cardDeck);
				break;
			default:
				break;
			}

			if (_currentState == GameStates::RONDEN) {
				_rondeController.startRound(controller, *this, _cardDeck);
			}
		}
	}
}

void GameController::setupGame(Controller& controller)
{
	bool check = true;
	
	
	if (!createCardDeck(controller))
	{
		check = false;
	}

	if (!createKarakterDeck(controller))
	{
		check = false;
	}

	if (check)
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
		controller.printToPlayer("Het karakter: " + _kaartenOpTafel.at(0)->getName() + " is omgekerd op tafel gelegd!", _currectPlayer.get_name());
		controller.printToPlayer("Kies een van de karakters voor in je hand:", _currectPlayer.get_name());

		for (int i = 0; i < _karakterDeck.getDeck().size(); ++i) {
			controller.printToPlayer(std::to_string(i + 1) + ": " + _karakterDeck.getDeck().at(i)->getName(), _currectPlayer.get_name());
		}
	}
	else
	{
		//stop game 
	}
}

Player& GameController::getPlayer1()
{
	return _player1;
}

Player & GameController::getCurrentPlayer()
{
	return _currectPlayer;
}

Player& GameController::getPlayer2()
{
	return _player2;
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

IKarakter & GameController::getKarakterByName(std::string name)
{
	for (std::shared_ptr<IKarakter> k : _karakterDeck.getDeck())
	{
		if (k->getName() == name)
		{
			return *k.get();
		}
	}
}

void GameController::legKaartOpTafel(std::shared_ptr<IKarakter> karakter)
{
	_kaartenOpTafel.push_back(karakter);
}

void GameController::setState(const GameStates state)
{
	_currentState = state;
}

void GameController::endGame(Controller& controller)
{
	toggleCurrentPlayer();
	int scorePlayer1 = getPlayer1().calculateScore();
	int scorePlayer2 = getPlayer2().calculateScore();

	if (scorePlayer1 > scorePlayer2) {
		controller.printLine(getPlayer1().get_name() + " heeft de game gewonnen met " + std::to_string(scorePlayer1) + " punten!");
	}
	else {
		controller.printLine(getPlayer1().get_name() + " heeft de game gewonnen met " + std::to_string(scorePlayer1) + " punten!");
	}

	controller.stop();


}



bool GameController::createCardDeck(Controller& con)
{
	try {
		std::ifstream file(_cardPath);

		//when file is missing throw exception
		if (!file)
		{
			throw std::exception();
		}

		while (file.good())
		{
			file >> _cardDeck;
		}

		file.close();
		_cardDeck.CreateCardDeck();

		return true;
	}
	catch (...)
	{
		con.printLine("Something went wrong during creating the building card deck.");
		con.printLine("Please make sure both card files are in the game map.");

		return false;
	}
	
}

bool GameController::createKarakterDeck(Controller& con)
{
	try {
		std::ifstream file(_karakterPath);

		//when file is missing throw exception
		if (!file)
		{
			throw std::exception();
		}

		while (file.good())
		{
			file >> _karakterDeck;
		}

		file.close();
		_karakterDeck.CreateIKarakterDeck();

		return true;
	}
	catch (...)
	{
		con.printLine("Something went wrong during creating the character card deck.");
		con.printLine("Please make sure both card files are in the game map.");

		return false;
	}
}
	
