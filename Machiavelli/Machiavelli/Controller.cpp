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

				
				//controleerd of de speler niet al gejoid is.
				if (checkSocket(clientInfo.get()) && playerSockets.size() > 0)
				{
					clientInfo->get_socket().write("je bent de game al gejoind. \r\n");
				}
				else
				{
					//controleerd of er al een speler is met dezelfde naam
					//zoja, dan geef deze speler een 2 achter zijn naam, om problemen te verkomen.
					if (players.size() > 0 && clientInfo->get_player().get_name() == players[0].get_name())
					{
						clientInfo->get_player().set_name(clientInfo->get_player().get_name() + "2");
						clientInfo->get_socket().write("Er is al een speler met dezelfde naam, je naam wordt aangepast naar: " + clientInfo->get_player().get_name() + "\r\n");
					}
					
					clientInfo->get_socket().write("je bent de game gejoind \r\n");

					//zet speler in de speler lijst.
					players.push_back(clientInfo->get_player());
					
					std::shared_ptr<ClientInfo> cinfo{ clientInfo };
					playerSockets.insert({ clientInfo->get_player().get_name(), cinfo });
					if (players.size() == 2) {
						started = true;
						_gameController.setupGame(*this);

					}
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

bool Controller::checkSocket(ClientInfo* ci)
{
	for (auto socket : playerSockets)
	{
		if (socket.second.get() == ci)
		{
			return true;
		}
	}

	return false;
}
