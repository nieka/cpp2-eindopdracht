#include "Moordenaar.h"
#include "Controller.h"


Moordenaar::Moordenaar()
{
	_name = "Moordenaar";
}


Moordenaar::~Moordenaar()
{
}

void Moordenaar::play(Controller & controller, GameController & gcon)
{
	int counter = 1;
	std::vector<std::string> names;
	controller.printToPlayer("welk karakter wil je vermoorden", gcon.getCurrentPlayer().get_name());

	for (std::shared_ptr<IKarakter> k : gcon.getKarakterCards().getDeck())
	{
		if (k->getName() != "Moordenaar")
		{
			controller.printToPlayer(std::to_string(counter) + " " + k->getName(), gcon.getCurrentPlayer().get_name());
			names.push_back(k->getName());
			++counter;
		}
	}

	bool a = false;

	while (!a)
	{
		std::string input = controller.readLineOfPlayer(gcon.getCurrentPlayer().get_name());
		int id = std::stoi(input);
		
		if (id > 0 && id < gcon.getKarakterCards().getDeck().size())
		{
			kill(names.at(id - 1), controller, gcon);
			controller.printToPlayer("je hebt de " + names.at(id - 1) + " vermoord", gcon.getCurrentPlayer().get_name());
			a = true;
		}
		
	}

}

void Moordenaar::kill(std::string name, Controller & controller, GameController & gcon)
{
	gcon.getKarakterByName(name).setKilled(true);
}
