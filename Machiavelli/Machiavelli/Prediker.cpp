#include "Prediker.h"
#include "Controller.h"


Prediker::Prediker()
{
	_name = "Prediker";
	
}


Prediker::~Prediker()
{
}

void Prediker::karakterInfo(Controller & controller, GameController & gcon)
{
	controller.printToPlayer("type 1 om de goudstukken te krijgen die je als predieker verdient", gcon.getCurrentPlayer().get_name());
}

bool Prediker::play(int input, Controller & controller, GameController & gcon)
{
	if (input == 1) {
		int goudstukken = 0;
		//geef de karakter voor elk blauw gebouw een goudstuk
		for each (auto bouwkaart in gcon.getCurrentPlayer().getGebouwdeKaarten())
		{
			if (bouwkaart->getColor() == "blauw") {
				goudstukken++;
			}
		}		

		gcon.getCurrentPlayer().addGoudStukken(goudstukken);
		controller.printToPlayer("Je hebt er " + std::to_string(goudstukken) + " bij gekregen en hebt nu " + std::to_string(gcon.getCurrentPlayer().getGoudstukken()), gcon.getCurrentPlayer().get_name());
	}
	else {
		controller.printToPlayer("Je hebt geen goudstukken gekregen", gcon.getCurrentPlayer().get_name());
	}
	return true;
}