#include "Koopman.h"
#include "Controller.h"

Koopman::Koopman()
{
	_name = "Koopman";
}


Koopman::~Koopman()
{
}

void Koopman::karakterInfo(Controller & controller, GameController & gcon)
{
	controller.printToPlayer("type 1 om de goudstukken te krijgen die je als koopman verdient", gcon.getCurrentPlayer().get_name());
}

bool Koopman::play(int input, Controller & controller, GameController & gcon)
{
	if (input == 1) {
		int goudstukken = 1;
		//geef de karakter voor elk blauw gebouw een goudstuk
		for each (auto bouwkaart in gcon.getCurrentPlayer().getGebouwdeKaarten())
		{
			if (bouwkaart->getColor() == "groen") {
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