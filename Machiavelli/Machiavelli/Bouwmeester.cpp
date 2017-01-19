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
}

bool Bouwmeester::play(int input, Controller & controller, GameController & gcon)
{
	/*
		Hij trekt 2 gebouwenkaarten. De bouwmeester mag in zijn beurt tot 3 gebouwenkaarten uitleggen. De
		bouwmeester kan derhalve aan het einde van het spel als enige meer dan 8 gebouwen bezitten.
	*/

	return true;
}
