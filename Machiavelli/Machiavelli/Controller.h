#pragma once
#include <memory>
#include <fstream>
#include <istream>
#include <Iostream>
#include <string>
#include "ClientCommand.h"
#include <string>
#include "Player.h"
#include "Socket.h"
#include "GameController.h"
#include <map>

class Controller
{
public:
	Controller();
	~Controller();

	void handleCommand(ClientCommand command);
	void printLine(const std::string value) const;
	void printToPlayer(const std::string value, const std::string playerName) const;
	void readLineOfPlayer(const std::string playerName) const;
	std::vector<Player> getPlayers() const;
private:
	bool started = false;

	//pointers required for inheritance of the karakter cards
	Deck<std::unique_ptr<Card>> _cardDeck;
	Deck<std::unique_ptr<IKarakter>> _karakterDeck;
	std::vector<Player> players;
	std::map<std::string,std::shared_ptr<ClientInfo>> playerSockets;
	GameController _gameController;
	const std::string _cardPath = "Bouwkaarten.csv";
	const std::string _karakterPath = "karakterkaarten.csv";
	bool checkSocket(ClientInfo* ci);
};

