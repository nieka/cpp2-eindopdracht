#include "KarakterVedelingController.h"
#include "GameController.h"
#include "Controller.h"

KarakterVedelingController::KarakterVedelingController()
{
}


KarakterVedelingController::~KarakterVedelingController()
{
}

void KarakterVedelingController::HandleGameCommands(ClientCommand command, Controller& controller,GameController& gameController)
{
	switch (std::stoi(command.get_cmd()))
	{
		case 1:
			gameController.getCurrentPlayer().AddKarakterKaart(gameController.getKarakterCards().getDeck().at(0));
			break;
		case 2:
			gameController.getCurrentPlayer().AddKarakterKaart(gameController.getKarakterCards().getDeck().at(1));
			break;
		case 3:
			gameController.getCurrentPlayer().AddKarakterKaart(gameController.getKarakterCards().getDeck().at(2));
			break;
		case 4:
			gameController.getCurrentPlayer().AddKarakterKaart(gameController.getKarakterCards().getDeck().at(3));
			break;
		case 5:
			gameController.getCurrentPlayer().AddKarakterKaart(gameController.getKarakterCards().getDeck().at(4));
			break;
		case 6:
			gameController.getCurrentPlayer().AddKarakterKaart(gameController.getKarakterCards().getDeck().at(5));
			break;
		case 7:
			gameController.getCurrentPlayer().AddKarakterKaart(gameController.getKarakterCards().getDeck().at(6));
			break;
		case 8:
			gameController.getCurrentPlayer().AddKarakterKaart(gameController.getKarakterCards().getDeck().at(7));
			break;
		default:
			controller.printToPlayer("Kies een nummer uit de lijst.", gameController.getCurrentPlayer().get_name());
			return;
	}

}
