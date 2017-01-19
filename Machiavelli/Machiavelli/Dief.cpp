#include "Dief.h"
#include "Controller.h"

Dief::Dief()
{
	_name = "Dief";
}


Dief::~Dief()
{
}

void Dief::karakterInfo(Controller & controller, GameController & gcon)
{
	int counter = 1;

	controller.printToPlayer("welk karakter wil je bestelen", gcon.getCurrentPlayer().get_name());


	if (_names.size() == 0)
	{
		for (std::shared_ptr<IKarakter> k : gcon.getKarakterCards().getDeck())
		{
			if (k->getName() != "Dief" || k->getName() != "Moordenaar" || k->getKilled())
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

bool Dief::play(int input, Controller & controller, GameController & gcon)
{
	if (input > 0 && input < gcon.getKarakterCards().getDeck().size())
	{
		Steal(_names.at(input - 1), controller, gcon);
		controller.printToPlayer("je hebt de " + _names.at(input - 1) + " bestolen", gcon.getCurrentPlayer().get_name());
		return true;
	}
}

void Dief::Steal(std::string name, Controller & controller, GameController & gcon)
{
	gcon.getKarakterByName(name).setTarget(true);
}
