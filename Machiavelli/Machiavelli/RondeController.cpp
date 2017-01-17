#include "RondeController.h"
#include "GameController.h"
#include "Controller.h"


RondeController::RondeController()
{
	counter = 0;
	inRound = false;
	gotReward = false;
	abilityUsed = false;
	_oproepVolgorde = { "Moordenaar", "Dief", "Magiër", "Koning","Prediker","Koopman","Bouwmeester","Condottiere" };
}


RondeController::~RondeController()
{
}

void RondeController::HandleGameCommands(ClientCommand command, Controller & controller, GameController & gameController, Deck<std::shared_ptr<Card>> cardDeck)
{	
	if (command.get_cmd() == "ability" && !abilityUsed)
	{
		gameController.getCurrentPlayer().playKarakterAbility(controller, currentKarakter);
		abilityUsed = true;
	}
	else if (command.get_cmd() == "end" && gotReward)
	{
		inRound = false;
		gotReward = false;
		abilityUsed = false;
		startRound(controller, gameController, cardDeck);
	}
	else
	{
		if (!gotReward)
		{
			int nr = std::stoi(command.get_cmd());
			switch (nr)
			{
			case(1):
				gameController.getCurrentPlayer().addGoudStukken(2);
				controller.printToPlayer("je hebt 2 goudstukken erbij gekregen", gameController.getCurrentPlayer().get_name());
				controller.printToPlayer("je hebt nu " + std::to_string(gameController.getCurrentPlayer().getGoudstukken()) + " goudstukken", gameController.getCurrentPlayer().get_name());
				gotReward = true;
				break;
			case(2):
				controller.printToPlayer("Kies 1 van de volgende kaarten", gameController.getCurrentPlayer().get_name());
				//bouwkaarten gedeelte
				gotReward = true;
			default:
				controller.printToPlayer("niet het juiste nummer", gameController.getCurrentPlayer().get_name());
				break;
			}
		}
	}

	printRoundInfo(controller, gameController);
}

void RondeController::startRound(Controller & controller, GameController & gameController, Deck<std::shared_ptr<Card>> cardDeck)
{
	if (!inRound) {
		bool playerHasCard = false;		
		std::string karakterCardName;
		while (!playerHasCard) {
			currentKarakter = _oproepVolgorde.at(counter);
			controller.printLine("De koning roeps de " + karakterCardName + " op!");
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
	if (!gotReward)
	{
		controller.printToPlayer("kies een van de volgende opties", gameController.getCurrentPlayer().get_name());
		controller.printToPlayer("1: 2 goudstukken", gameController.getCurrentPlayer().get_name());
		controller.printToPlayer("2: een gebouwkaart", gameController.getCurrentPlayer().get_name());
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