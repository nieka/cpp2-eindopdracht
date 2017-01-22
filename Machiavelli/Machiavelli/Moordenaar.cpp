#include "Moordenaar.h"
#include "Controller.h"

Moordenaar::Moordenaar()
{
	_name = "Moordenaar";
}


Moordenaar::~Moordenaar()
{
}

void Moordenaar::karakterInfo(Controller & controller, GameController & gcon)
{
	int counter = 1;
	
	controller.printToPlayer("welk karakter wil je vermoorden", gcon.getCurrentPlayer().get_name());

	
	if (_names.size() == 0)
	{
		for each(std::shared_ptr<IKarakter> k in gcon.getKarakterCards().getDeck())
		{
			if (k->getName() != "Moordenaar")
			{
				_names.push_back(k->getName());
			}
		}
	}
	
	for (std::string k : _names)
	{
		controller.printToPlayer(std::to_string(counter) + " " + k, gcon.getCurrentPlayer().get_name());
		++counter;
	}
	
}

bool Moordenaar::play(int input, Controller & controller, GameController & gcon)
{

		
	if (input > 0 && input < gcon.getKarakterCards().getDeck().size())
	{
		controller.printToPlayer("je hebt de " + _names.at(input - 1) + " vermoord", gcon.getCurrentPlayer().get_name());
		gcon.getKarakterByName(_names.at(input - 1)).setKilled(true);
		return true;
	}

	return false;
}
