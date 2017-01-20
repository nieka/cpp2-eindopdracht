#include "Koning.h"
#include "Controller.h"

Koning::Koning()
{
	_name = "Koning";
}


Koning::~Koning()
{
}

void Koning::karakterInfo(Controller & controller, GameController & gcon)
{
	controller.printToPlayer("type 1 om de goudstukken te krijgen die je als koning verdient", gcon.getCurrentPlayer().get_name());
}

bool Koning::play(int input, Controller & controller, GameController & gcon)
{
	if (input == 1) {
		int goudstukken = 1;
		//geef de karakter voor elk blauw gebouw een goudstuk
		for each (auto bouwkaart in gcon.getCurrentPlayer().getGebouwdeKaarten())
		{
			if (bouwkaart->getColor() == "geel") {
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