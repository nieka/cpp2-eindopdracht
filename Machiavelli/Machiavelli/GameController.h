#pragma once
#include "Player.h"
#include "ClientCommand.h"
#include "Deck.h"
#include "Card.h"
#include "IKarakter.h"
#include "KarakterVedelingController.h"
#include "RondeController.h"
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
	Player getPlayer1() const;
	Player getPlayer2() const;


	void toggleCurrentPlayer();
	Deck<std::shared_ptr<IKarakter>> getKarakterCards() const;
	void legKaartOpTafel(std::shared_ptr<IKarakter> karakter);
	void setState(const GameStates state);

private:
	bool createCardDeck(Controller& con);
	bool createKarakterDeck(Controller& con);

	Deck<std::shared_ptr<Card>> _cardDeck;
	Deck<std::shared_ptr<IKarakter>> _karakterDeck;
	Player _player1;
	Player _player2;
	Player _currectPlayer;
	KarakterVedelingController _karakterVerdelingController;
	RondeController _rondeController;
	GameStates _currentState;
	std::vector<std::shared_ptr<IKarakter>> _kaartenOpTafel;
	const std::string _cardPath = "Bouwkaarten.csv";
	const std::string _karakterPath = "karakterkaarten.csv";
	
};

