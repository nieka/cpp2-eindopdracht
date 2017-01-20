#include "Bouwmeester.h"
#include "Controller.h"

Bouwmeester::Bouwmeester()
{
	_name = "Bouwmeester";
}


Bouwmeester::~Bouwmeester()
{
}

void Bouwmeester::karakterInfo(Controller & controller, GameController & gcon)
{
	controller.printToPlayer("type 1 om 2 extra gebouwkaarten te pakken", gcon.getCurrentPlayer().get_name());
}

bool Bouwmeester::play(int input, Controller & controller, GameController & gcon)
{
	/*
		Hij trekt 2 gebouwenkaarten. De bouwmeester mag in zijn beurt tot 3 gebouwenkaarten uitleggen. De
		bouwmeester kan derhalve aan het einde van het spel als enige meer dan 8 gebouwen bezitten.
	*/
	if (input == 1) {

		gcon.getCurrentPlayer().AddBouwCard(gcon.getBouwKaarten().drawCard());
		controller.printToPlayer("Je hebt de bouwkaart " + gcon.getCurrentPlayer().getBouwKaarten().at(gcon.getCurrentPlayer().getBouwKaarten().size() -1)->getName() + " ontvangen", gcon.getCurrentPlayer().get_name());
		gcon.getCurrentPlayer().AddBouwCard(gcon.getBouwKaarten().drawCard());
		controller.printToPlayer("Je hebt de bouwkaart " + gcon.getCurrentPlayer().getBouwKaarten().at(gcon.getCurrentPlayer().getBouwKaarten().size() - 1)->getName() + " ontvangen", gcon.getCurrentPlayer().get_name());
	}
	else {
		controller.printToPlayer("Je hebt geen bouwkaarten ontvangen", gcon.getCurrentPlayer().get_name());
	}

	return true;
}
