#include "Controller.h"
#include "Player.h"
#include "ClientInfo.h"
#include "Socket.h"

Controller::Controller()
{
	createDeck("Bouwkaarten.csv");
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
			_gameController.HandleGameCommands(command,*this);
		}		
	}
}

void Controller::createDeck(std::string filepath)
{
	std::ifstream file(filepath);

	while (file.good())
	{
		file >> deck;
	}
	file.close();

	deck.shuffleDeck();
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
