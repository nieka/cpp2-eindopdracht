#include "Condottiere.h"
#include "Controller.h"


Condottiere::Condottiere()
{
	_name = "Condottiere";
}


Condottiere::~Condottiere()
{
}

void Condottiere::karakterInfo(Controller & controller, GameController & gcon)
{
	controller.printToPlayer("Welk gebouw van de tegenstander wil je weghalen", gcon.getCurrentPlayer().get_name());
	int counter = 1;

	if (gcon.getPlayer1().get_name() == gcon.getCurrentPlayer().get_name())
	{
		for (std::shared_ptr<Card> c : gcon.getPlayer2().getGebouwdeKaarten())
		{
			controller.printToPlayer(std::to_string(counter) + " " + c->getName(), gcon.getCurrentPlayer().get_name());
			++counter;
		}
	}
	else
	{
		for (std::shared_ptr<Card> c : gcon.getPlayer1().getGebouwdeKaarten())
		{
			controller.printToPlayer(std::to_string(counter) + " " + c->getName(), gcon.getCurrentPlayer().get_name());
			++counter;
		}
	}
	
	
}

bool Condottiere::play(int input, Controller & controller, GameController & gcon)
{
	if (gcon.getPlayer1().get_name() == gcon.getCurrentPlayer().get_name())
	{
		if (input > 0 && input <= gcon.getPlayer2().getGebouwdeKaarten().size())
		{
			if (gcon.getPlayer2().getGebouwdeKaarten().at(input - 1)->getWaarde() < 2 || gcon.getCurrentPlayer().getGoudstukken() >= gcon.getPlayer2().getGebouwdeKaarten().at(input - 1)->getWaarde() - 1)
			{
				controller.printToPlayer("je hebt de " + gcon.getPlayer2().getGebouwdeKaarten().at(input - 1)->getName() + " verwijderd.", gcon.getCurrentPlayer().get_name());
				gcon.getCurrentPlayer().setGoudStukkken(gcon.getCurrentPlayer().getGoudstukken() - gcon.getPlayer2().getGebouwdeKaarten().at(input - 1)->getWaarde() - 1);
				gcon.getPlayer2().verwijderGebouw(input - 1);
				return true;
			}
			else
			{
				controller.printToPlayer("je hebt niet genoeg goudstukken om dit gebouw te verwijderen", gcon.getCurrentPlayer().get_name());
			}
			
		}
	}
	else
	{
		if (input > 0 && input <= gcon.getPlayer1().getGebouwdeKaarten().size())
		{
			if (gcon.getPlayer1().getGebouwdeKaarten().at(input - 1)->getWaarde() < 2 || gcon.getCurrentPlayer().getGoudstukken() >= gcon.getPlayer1().getGebouwdeKaarten().at(input - 1)->getWaarde() - 1)
			{
				controller.printToPlayer("je hebt de " + gcon.getPlayer1().getGebouwdeKaarten().at(input - 1)->getName() + " verwijderd.", gcon.getCurrentPlayer().get_name());
				gcon.getCurrentPlayer().setGoudStukkken(gcon.getCurrentPlayer().getGoudstukken() - gcon.getPlayer1().getGebouwdeKaarten().at(input - 1)->getWaarde() - 1);
				gcon.getPlayer1().verwijderGebouw(input - 1);

				return true;
			}
			else
			{
				controller.printToPlayer("je hebt niet genoeg goudstukken om dit gebouw te verwijderen", gcon.getCurrentPlayer().get_name());
			}
		}
	}
	
	return false;
}