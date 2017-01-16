#include "Controller.h"
#include "Player.h"
#include "ClientInfo.h"
#include "Socket.h"

Controller::Controller()
{
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
				//playerSockets.insert({clientInfo->get_player().get_name(), std::move(clientInfo->get_socket()) });

				std::shared_ptr<ClientInfo> cinfo { clientInfo };
				playerSockets.insert({ clientInfo->get_player().get_name(), cinfo });
				if (players.size() == 2) {
					started = true;
					_gameController.setupGame(*this);

				}
			}
		}
		else {
			_gameController.HandleGameCommands(command, *this);
		}
	}
}

void Controller::printLine(const std::string value) const
{
	
	for (auto const& player : playerSockets) {
		player.second->get_socket().write(value + "\r\n");
	}
}

void Controller::printToPlayer(const std::string value, const std::string playerName) const
{
	playerSockets.at(playerName)->get_socket().write(value + "\r\n");
}

std::vector<Player> Controller::getPlayers() const
{
	return players;
}
