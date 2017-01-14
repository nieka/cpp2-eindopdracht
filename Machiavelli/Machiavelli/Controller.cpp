#include "Controller.h"
#include "Player.h"
#include "ClientInfo.h"
#include "Socket.h"

Controller::Controller()
{
	createCardDeck();

}


Controller::~Controller()
{
}

void Controller::handleCommand(ClientCommand command)
{
	if (auto clientInfo = command.get_client_info().lock()) {
		if (!started) {
			if (command.get_cmd() == "join") {
				players.push_back(clientInfo->get_player());
				playerSockets.push_back(std::move(clientInfo->get_socket()));
				if (players.size() == 2) {
					started = true;
					_gameController.setupGame(*this);
					printLine("The game begins");
				}
			}
		}
		else {
			_gameController.HandleGameCommands(command, *this);
		}
	}
}

void Controller::createCardDeck()
{
	std::ifstream file(_cardPath);
	while (file.good())
	{
		file >> _cardDeck;
	}

	file.close();

	_cardDeck.shuffleDeck();
}

void Controller::createKarakterDeck()
{
	/*
	std::ifstream file(_karakterPath);
	while (file.good())
	{
		file >> _karakterDeck;
	}

	file.close();

	_karakterDeck.shuffleDeck();
	*/
}

void Controller::printLine(const std::string value)
{
	for (int i = 0; i < playerSockets.size(); ++i) {
		playerSockets.at(i).write(value);
	}
}

std::vector<Player> Controller::getPlayers()
{
	return players;
}
