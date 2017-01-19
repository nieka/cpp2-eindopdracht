#include "RondeController.h"
#include "GameController.h"
#include "Controller.h"


RondeController::RondeController()
{
	counter = 0;
	_roundType = CHOOSING;
	inRound = false;
	gotReward = false;
	abilityUsed = false;
	_oproepVolgorde = { "Moordenaar", "Dief", "Magiër", "Koning","Prediker","Koopman","Bouwmeester","Condottiere" };
	currentKarakter = _oproepVolgorde.at(0);
}


RondeController::~RondeController()
{
}

void RondeController::HandleGameCommands(ClientCommand command, Controller & controller, GameController & gameController, Deck<std::shared_ptr<Card>> cardDeck)
{	
	if (command.get_cmd() == "ability" && !abilityUsed)
	{
		_lastType = _roundType;
		_roundType = ABILITY;
		gameController.getKarakterByName(currentKarakter).play(controller, gameController);
		abilityUsed = true;
		_roundType = _lastType;
		//printRoundInfo(controller, gameController);
	}
	else if (command.get_cmd() == "end" && gotReward)
	{
		inRound = false;
		gotReward = false;
		abilityUsed = false;
		_roundType = CHOOSING;
		startRound(controller, gameController, cardDeck);
	}
	else
	{
		switch (_roundType)
		{
		case (CHOOSING):
			switch (std::stoi(command.get_cmd()))
			{
			case(1) :
				gameController.getCurrentPlayer().addGoudStukken(2);
				controller.printToPlayer("je hebt 2 goudstukken erbij gekregen", gameController.getCurrentPlayer().get_name());
				controller.printToPlayer("je hebt nu " + std::to_string(gameController.getCurrentPlayer().getGoudstukken()) + " goudstukken", gameController.getCurrentPlayer().get_name());
				gotReward = true;
				printRoundInfo(controller, gameController);
				_lastType = CHOOSING;
				_roundType = BUILD;
				break;
			case(2) :
				controller.printToPlayer("Kies 1 van de volgende kaarten om in je hand te nemen. De andere word op de afleg stapel gelegd.", gameController.getCurrentPlayer().get_name());
				//bouwkaarten gedeelte
				gotReward = true;
				printRoundInfo(controller, gameController);
				_lastType = CHOOSING;
				_roundType = GETBUILDCARD;
				for (int i = 0; i < 2; ++i) {
					_tempBouwkaarten.push_back(cardDeck.drawCard());
					controller.printToPlayer(std::to_string(i + 1) + " " + _tempBouwkaarten.back()->getName(), gameController.getCurrentPlayer().get_name());
				}
			default:
				controller.printToPlayer("niet het juiste nummer", gameController.getCurrentPlayer().get_name());
				break;
			}
			break;
		case(GETBUILDCARD) :
			{
				//get buildt card
				int nr = std::stoi(command.get_cmd());
				if (nr == 1 || nr == 2) {
					gameController.getCurrentPlayer().AddBouwCard(_tempBouwkaarten.at(nr - 1));
					//we maken de lijst weer leeg. De andere bouwkaart moet naar de afleg stapen dus die verwijderen we uit de game
					_tempBouwkaarten.clear();
					_lastType = GETBUILDCARD;
					_roundType = BUILD;
				}
				else {
					controller.printToPlayer("niet het juiste nummer", gameController.getCurrentPlayer().get_name());
				}
				break;
			}
		case (BUILD) :
			//gebruik bouwkaart of doe niks
			break;
		case(ABILITY):
			
				break;
		default:
			break;
		}
	}

	printRoundInfo(controller, gameController);
}

void RondeController::startRound(Controller & controller, GameController & gameController, Deck<std::shared_ptr<Card>> cardDeck)
{
	if (!inRound) {
		bool playerHasCard = false;		
		while (!playerHasCard) {

			if (gameController.getKarakterByName(currentKarakter).getKilled())
			{
				controller.printLine("de moordenaar heeft " + currentKarakter + " vermoord.");
				++counter;
				if (counter == _oproepVolgorde.size()) {
					counter = 0;
				}
			}
			else if (gameController.getKarakterByName(currentKarakter).getTarget())
			{
				controller.printLine("de dief heeft " + currentKarakter + " bestolen.");
			}

			currentKarakter = _oproepVolgorde.at(counter);
			controller.printLine("De koning roeps de " + currentKarakter + " op!");
			//check if player 1 or two has the card
			if (gameController.getPlayer1().hasKarakterKaart(currentKarakter)) {
				playerHasCard = true;
				if (gameController.getCurrentPlayer().get_name() != gameController.getPlayer1().get_name()) {
					gameController.toggleCurrentPlayer();
				}
			}
			else if (gameController.getPlayer2().hasKarakterKaart(currentKarakter)) {
				playerHasCard = true;
				if (gameController.getCurrentPlayer().get_name() != gameController.getPlayer2().get_name()) {
					gameController.toggleCurrentPlayer();
				}
			}
			counter++;
			if (counter == _oproepVolgorde.size()) {
				counter = 0;
			}
		}	

		if (playerHasCard) {
			//the current player has the card so we have a turn
			inRound = true;
			controller.printLine(gameController.getCurrentPlayer().get_name() + " heef het karakter kaart " + currentKarakter + " en is nu aan de buurt om iets te doen.");
			printRoundInfo(controller, gameController);
		}
	}
}

void RondeController::printRoundInfo(Controller & controller, GameController & gameController)
{
	switch (_roundType)
	{
		case (CHOOSING):
			controller.printToPlayer("kies een van de volgende opties", gameController.getCurrentPlayer().get_name());
			controller.printToPlayer("1: 2 goudstukken", gameController.getCurrentPlayer().get_name());
			controller.printToPlayer("2: een gebouwkaart", gameController.getCurrentPlayer().get_name());
			break;
		case (BUILD):
			controller.printToPlayer("kies een je bouwkaarten om te bouwen", gameController.getCurrentPlayer().get_name());
			for(int i = 0; i < gameController.getCurrentPlayer().getBouwKaarten().size(); ++i)
			{
				controller.printToPlayer(std::to_string(i +1) + ": " + gameController.getCurrentPlayer().getBouwKaarten().at(i)->getName(), gameController.getCurrentPlayer().get_name());
			}
			break;
		case (END):
			controller.printToPlayer("type 'end' om de buurt te eindigen.", gameController.getCurrentPlayer().get_name());
			break;
		default:
			break;
	}
	
	if (!abilityUsed)
	{
		controller.printToPlayer("type 'ability' om je karakter ability te gebruiken", gameController.getCurrentPlayer().get_name());
	}

	if (gotReward)
	{
		controller.printToPlayer("type 'end' om de buurt te eindigen.", gameController.getCurrentPlayer().get_name());
	}
	
}
