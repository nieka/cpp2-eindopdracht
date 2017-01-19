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
	//std::vector<std::string> _names;
	
	int counter = 1;
	
	controller.printToPlayer("welk karakter wil je vermoorden", gcon.getCurrentPlayer().get_name());

	
	if (_names.size() == 0)
	{
		for (std::shared_ptr<IKarakter> k : gcon.getKarakterCards().getDeck())
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
		kill(_names.at(input - 1), controller, gcon);
		controller.printToPlayer("je hebt de " + _names.at(input - 1) + " vermoord", gcon.getCurrentPlayer().get_name());
		return true;
	}

	return false;
}

void Moordenaar::kill(std::string name, Controller & controller, GameController & gcon)
{
	gcon.getKarakterByName(name).setKilled(true);
}
