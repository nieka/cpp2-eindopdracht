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
			bool check = true;

			if (k->getName() == "Dief")
			{
				check = false;
			}

			if (k->getName() == "Moordenaar")
			{
				check = false;
			}

			if (k->getKilled())
			{
				check = false;
			}

			if (check)
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
		controller.printToPlayer("je hebt de " + _names.at(input - 1) + " bestolen", gcon.getCurrentPlayer().get_name());
		gcon.getKarakterByName(_names.at(input - 1)).setTarget(true);
		return true;
	}

	return false;
}
