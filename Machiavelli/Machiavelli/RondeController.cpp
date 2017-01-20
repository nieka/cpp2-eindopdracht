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
	_firstTomaxBuildings = false;
	_oproepVolgorde = { "Moordenaar", "Dief", "Magier", "Koning","Prediker","Koopman","Bouwmeester","Condottiere" };
	currentKarakter = _oproepVolgorde.at(0);
}


RondeController::~RondeController()
{
}

void RondeController::HandleGameCommands(ClientCommand command, Controller & controller, GameController & gameController, Deck<std::shared_ptr<Card>> cardDeck)
{	
	if (command.get_cmd() == "ability" && !abilityUsed && _roundType != RoundType::ABILITY)
	{
		_lastType = _roundType;
		_roundType = ABILITY;
	}
	else
	{
		switch (_roundType)
		{
		case (CHOOSING):
			switch (std::stoi(command.get_cmd()))
			{
			case(1):
				gameController.getCurrentPlayer().addGoudStukken(2);
				controller.printToPlayer("je hebt 2 goudstukken erbij gekregen", gameController.getCurrentPlayer().get_name());
				controller.printToPlayer("je hebt nu " + std::to_string(gameController.getCurrentPlayer().getGoudstukken()) + " goudstukken", gameController.getCurrentPlayer().get_name());
				gotReward = true;
				_lastType = CHOOSING;
				_roundType = BUILD;
				break;
			case(2):
				controller.printToPlayer("Kies 1 van de volgende kaarten om in je hand te nemen. De andere word op de afleg stapel gelegd.", gameController.getCurrentPlayer().get_name());
				//bouwkaarten gedeelte
				gotReward = true;
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
		case(GETBUILDCARD):
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
		case (BUILD):
		{
			//gebruik bouwkaart of doe niks
			if (command.get_cmd() == "geen") {
				//de speller wil niks bouwen dus we gaan verder met de ronde
				_roundType = END;
				break;
			}
			int buildNumber = std::stoi(command.get_cmd());
			if (buildNumber > 0 && buildNumber < gameController.getCurrentPlayer().getBouwKaarten().size()) {
				std::shared_ptr<Card> bouwkaart = gameController.getCurrentPlayer().getBouwKaarten().at(buildNumber - 1);
				if (bouwkaart->getWaarde() <= gameController.getCurrentPlayer().getGoudstukken()) {
					gameController.getCurrentPlayer().bouwGebouw(bouwkaart);
					if (gameController.getCurrentPlayer().getGebouwdeKaarten().size() == BUILDINGSNEEDEDTOWIN && !_firstTomaxBuildings) {
						_firstTomaxBuildings = true;
						gameController.getCurrentPlayer().setFirstToMaxBuildeings();
					}
					if (currentKarakter == "Bouwmeester" && _gebouwdeGebouwen <= 3) {
						_gebouwdeGebouwen++;
						controller.printToPlayer("Omdat je een bouwmeester bent mag je nog een gebouw bouwen", gameController.getCurrentPlayer().get_name());

					}
					else {
						_roundType = END;
						_gebouwdeGebouwen = 0;
					}					
				}
				else {
					controller.printToPlayer("Je hebt niet genoeg goudstukken om het gebouw te bouwen", gameController.getCurrentPlayer().get_name());
				}
			}
			else {
				controller.printToPlayer("niet het juiste nummer", gameController.getCurrentPlayer().get_name());
			}
			break;
		}
		case(ABILITY):
		{
			int input = std::stoi(command.get_cmd());

			if (gameController.getKarakterByName(currentKarakter).play(input, controller, gameController))
			{
				abilityUsed = true;
				_roundType = _lastType;
			}
			else
			{
				controller.printToPlayer("voer het juiste getal in.", gameController.getCurrentPlayer().get_name());
			}

			break;
		}

		case (END):
			if (command.get_cmd() == "end") {
				inRound = false;
				gotReward = false;
				abilityUsed = false;
				_roundType = CHOOSING;
				startRound(controller, gameController, cardDeck);
			}
		default:
			break;
		}
	}

	printRoundInfo(controller, gameController);
}

void RondeController::startRound(Controller & controller, GameController & gameController, Deck<std::shared_ptr<Card>> cardDeck)
{
	//check of de game is afgelopen
	if (gameController.getPlayer1().getGebouwdeKaarten().size() == BUILDINGSNEEDEDTOWIN || gameController.getPlayer2().getGebouwdeKaarten().size() == BUILDINGSNEEDEDTOWIN) {
		//de game is afgelopen
		gameController.endGame(controller);
		return;
	}
	if (!inRound) {
		bool playerHasCard = false;		
		while (!playerHasCard) {
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

			if (gameController.getKarakterByName(currentKarakter).getKilled())
			{
				controller.printLine("de moordenaar heeft " + currentKarakter + " vermoord.");			
				if (counter == _oproepVolgorde.size()) {
					counter = 0;
				}

			}
			else if (gameController.getKarakterByName(currentKarakter).getTarget())
			{
				controller.printLine("de dief heeft de " + currentKarakter + " bestolen.");
				int goud = gameController.getCurrentPlayer().getGoudstukken();
				gameController.getCurrentPlayer().setGoudStukkken(0);
				controller.printToPlayer("je hebt nu " + std::to_string(gameController.getCurrentPlayer().getGoudstukken()) + " goudstukken.", gameController.getCurrentPlayer().get_name());
				if (gameController.getPlayer1().hasKarakterKaart("Dief"))
				{
					gameController.getPlayer1().addGoudStukken(goud);
					controller.printToPlayer("je hebt nu " + std::to_string(gameController.getPlayer1().getGoudstukken()) + " goudstukken.", gameController.getPlayer1().get_name());
				}
				else
				{
					gameController.getPlayer2().addGoudStukken(goud);
					controller.printToPlayer("je hebt nu " + std::to_string(gameController.getPlayer2().getGoudstukken()) + " goudstukken.", gameController.getPlayer2().get_name());
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
	//print gebouwde kaarten
	Player& currentPlayer = gameController.getCurrentPlayer();
	std::string name = currentPlayer.get_name();
	controller.printToPlayer("De voglende gebouwen heb je gebouwd:", name);
	for each (auto kaart in currentPlayer.getGebouwdeKaarten())
	{
		controller.printToPlayer(kaart->getName(), name);
	}

	switch (_roundType)
	{
		case (CHOOSING):
			controller.printToPlayer("kies een van de volgende opties", name);
			controller.printToPlayer("1: 2 goudstukken", name);
			controller.printToPlayer("2: een gebouwkaart", name);
			break;
		case (BUILD):
			controller.printToPlayer("kies een je bouwkaarten om te bouwen", name);
			for(int i = 0; i < currentPlayer.getBouwKaarten().size(); ++i)
			{
				controller.printToPlayer(std::to_string(i +1) + ": " + currentPlayer.getBouwKaarten().at(i)->getName(), name);
			}
			controller.printToPlayer("Of type geen om niks te bouwen", name);
			break;
		case(ABILITY):
			gameController.getKarakterByName(currentKarakter).karakterInfo(controller, gameController);
			break;
		case (END):
			controller.printToPlayer("type 'end' om de buurt te eindigen.", name);
			break;
		default:
			break;
	}
	
	if (!abilityUsed && _roundType != RoundType::ABILITY)
	{
		controller.printToPlayer("type 'ability' om je karakter ability te gebruiken", gameController.getCurrentPlayer().get_name());
	}	
}
