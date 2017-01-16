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

				if (players.size() > 0 && clientInfo->get_player().get_name() == players[0].get_name())
				{
					clientInfo->get_player().set_name(clientInfo->get_player().get_name() + "2");
					clientInfo->get_socket().write("Er is al een speler met dezlefde naam, je naam wordt aangepast naar: " + clientInfo->get_player().get_name() + "\r\n");
				}

				players.push_back(clientInfo->get_player());

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
