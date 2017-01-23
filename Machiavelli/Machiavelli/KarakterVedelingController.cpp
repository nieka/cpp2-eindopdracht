#include "KarakterVedelingController.h"
#include "GameController.h"
#include "Controller.h"

KarakterVedelingController::KarakterVedelingController()
{
	//we zetten de step hier al op 1 omdat in het begin de eerste kaart austomatisch omgekeerd op de tafel gelegd word en we dus niet hoeven te kiezen
	step = 1;
}


KarakterVedelingController::~KarakterVedelingController()
{
}

void KarakterVedelingController::HandleGameCommands(const ClientCommand command, Controller& controller,GameController& gameController, Deck<std::shared_ptr<IKarakter>>& karakterDeck)
{
	if (command.get_cmd() == "cheat")
	{
		if (karakterDeck.getDeck().size() == 8)
		{
			skipPhase(controller, gameController, karakterDeck);
		}
	}
	else
	{	
		int number = std::stoi(command.get_cmd());
		if (number >= 1 && number <= cards.size()) {
			std::shared_ptr<IKarakter> card = std::move(cards.at(number - 1));

			cards.erase(cards.begin() + number - 1);

			if (step == 0) {
				//leg kaart omgedraaid op tafel
				gameController.legKaartOpTafel(card);
				controller.printToPlayer("Het karakter: " + card->getName() + " is omgekerd op tafel gelegd!", gameController.getCurrentPlayer().get_name());
			}
			else {
				gameController.getCurrentPlayer().AddKarakterKaart(card);
				controller.printToPlayer("Het karakter: " + card->getName() + " is aan je hand toegevoegd!", gameController.getCurrentPlayer().get_name());
			}

			if (step == 0) {
				controller.printToPlayer("Kies een van de karakters om in je hand te nemen:", gameController.getCurrentPlayer().get_name());
				step++;
			}
			else {
				step = 0;
				if (cards.size() == 0) {
					//we zijn klaar met deze state
					controller.printLine("Het karakter verdelen is klaar!");
					gameController.setState(GameStates::RONDEN);
				}
				gameController.toggleCurrentPlayer();
				controller.printToPlayer("Kies een van de karakters om omgedraaid op tafel te leggen:", gameController.getCurrentPlayer().get_name());
			}

			for (int i = 0; i < cards.size(); ++i) {
				controller.printToPlayer(std::to_string(i + 1) + ": " + cards.at(i)->getName(), gameController.getCurrentPlayer().get_name());
			}
		}
		else {
			controller.printToPlayer("Kies een nummer uit de lijst.", gameController.getCurrentPlayer().get_name());
		}
	}
	
}

void KarakterVedelingController::start(Controller & controller, GameController & gameController, Deck<std::shared_ptr<IKarakter>>& karakterDeck)
{
	step = 1;
	//zorgt ervoor dat het deck voor de eerste keer wordt aangemaakt.
	cards = { karakterDeck.getDeck() };
	deck = true;

	std::shared_ptr<IKarakter> card = std::move(cards.at(cards.size() - 1));

	cards.erase(cards.end() - 1);

	controller.printLine(gameController.getCurrentPlayer().get_name() + " is de koning en mag beginnen.");


	gameController.legKaartOpTafel(card);
	controller.printToPlayer("Het karakter: " + card->getName() + " is omgekerd op tafel gelegd!", gameController.getCurrentPlayer().get_name());
	controller.printToPlayer("Kies een van de karakters voor in je hand:", gameController.getCurrentPlayer().get_name());

	for (int i = 0; i < cards.size(); ++i) {
		controller.printToPlayer(std::to_string(i + 1) + ": " + cards.at(i)->getName(), gameController.getCurrentPlayer().get_name());
	}
}

void KarakterVedelingController::skipPhase(Controller& controller, GameController& gameController, Deck<std::shared_ptr<IKarakter>>& karakterDeck)
{
	//need random seed
	srand(time(NULL));

	//leg karakter kaarten op tafel
	for (int i = 0; i < 3; ++i)
	{
			int id = rand() % cards.size();
			std::shared_ptr<IKarakter> card = std::move(cards.at(id));
			
			cards.erase(cards.begin() + id);

			gameController.legKaartOpTafel(card);
	}

	//geef spelers karakter kaarten
	for (int j = 0; j < 4; ++j)
	{
		int id = rand() % cards.size();
		std::shared_ptr<IKarakter> card = std::move(cards.at(id));
		
		cards.erase(cards.begin() + id);

		gameController.getCurrentPlayer().AddKarakterKaart(card);
		controller.printToPlayer("Het karakter: " + card->getName() + " is aan je hand toegevoegd!", gameController.getCurrentPlayer().get_name());
		gameController.toggleCurrentPlayer();
	}

	//we zijn klaar met deze state
	controller.printLine("----------------------Het karakter verdelen is klaar!----------------------");
	gameController.setState(GameStates::RONDEN);
}
