#pragma once
#include "Player.h"
#include "ClientCommand.h"
#include "Deck.h"
#include "Card.h"
#include "IKarakter.h"
#include "KarakterVedelingController.h"
#include "GameStates.h"

class IKarakter;
class Controller;
class ClientCommand;
class GameController
{
public:
	GameController();
	~GameController();

	void HandleGameCommands(ClientCommand command, Controller& controller);
	void setupGame(Controller& controller);
	Player& getCurrentPlayer();
		
	void karakterVerdeling(Controller& controller);

	Deck<std::shared_ptr<IKarakter>> getKarakterCards() const;

private:
	void createCardDeck();
	void createKarakterDeck();

	Deck<std::unique_ptr<Card>> _cardDeck;
	Deck<std::shared_ptr<IKarakter>> _karakterDeck;
	Player _player1;
	Player _player2;
	Player _currectPlayer;
	KarakterVedelingController karakterVerdelingController;
	GameStates _currentState;
	std::vector<std::shared_ptr<IKarakter>> _kaartenOpTafel;
	const std::string _cardPath = "Bouwkaarten.csv";
	const std::string _karakterPath = "karakterkaarten.csv";
	
};

