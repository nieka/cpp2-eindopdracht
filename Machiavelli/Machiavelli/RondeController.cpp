#include "RondeController.h"
#include "GameController.h"
#include "Controller.h"


RondeController::RondeController()
{
	counter = 0;
	inRound = false;
	_oproepVolgorde = { "Moordenaar", "Dief", "Magiër", "Koning","Prediker","Koopman","Bouwmeester","Condottiere" };
}


RondeController::~RondeController()
{
}

void RondeController::HandleGameCommands(ClientCommand command, Controller & controller, GameController & gameController, Deck<std::shared_ptr<Card>> cardDeck)
{	
	
}

void RondeController::startRound(Controller & controller, GameController & gameController, Deck<std::shared_ptr<Card>> cardDeck)
{
	if (!inRound) {
		bool playerHasCard = false;		
		std::string karakterCardName;
		while (!playerHasCard) {
			karakterCardName = _oproepVolgorde.at(counter);
			controller.printLine("De koning roeps de " + karakterCardName + " op!");
			//check if player 1 or two has the card
			if (gameController.getPlayer1().hasKarakterKaart(karakterCardName)) {
				playerHasCard = true;
				if (gameController.getCurrentPlayer().get_name() != gameController.getPlayer1().get_name()) {
					gameController.toggleCurrentPlayer();
				}
			}
			else if (gameController.getPlayer2().hasKarakterKaart(karakterCardName)) {
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
			controller.printLine(gameController.getCurrentPlayer().get_name() + " heef het karakter kaart " + karakterCardName + " en is nu aan de buurt om iets te doen.");
			printRoundInfo(controller, gameController);
		}
	}
}

void RondeController::printRoundInfo(Controller & controller, GameController & gameController)
{

}
