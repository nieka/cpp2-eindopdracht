#include "Magier.h"
#include "Controller.h"


Magier::Magier()
{
	_name = "Magier";
}


Magier::~Magier()
{
}

void Magier::karakterInfo(Controller & controller, GameController & gcon)
{
	controller.printToPlayer("Kies tussen de volgende opties:", gcon.getCurrentPlayer().get_name());
	controller.printToPlayer("1. ruil alle bouwkaarten met de andere speler", gcon.getCurrentPlayer().get_name());
	controller.printToPlayer("2. leg een aantal bouwkaarten af en pak trek hetzelfde aantal nieuwe kaarten", gcon.getCurrentPlayer().get_name());
}

bool Magier::play(int input, Controller & controller, GameController & gcon)
{
	if (input == 1)
	{
		std::vector<std::shared_ptr<Card>> speler1 = gcon.getPlayer1().getBouwKaarten();
		std::vector<std::shared_ptr<Card>> speler2 = gcon.getPlayer2().getBouwKaarten();
		gcon.getPlayer1().setBouwkaarten(speler2);
		gcon.getPlayer2().setBouwkaarten(speler1);
		controller.printLine("de magier gebruikt zijn ability om jullie bouwkaarten om te wisselen.");
		return true;
	}
	else if (input == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
		
}