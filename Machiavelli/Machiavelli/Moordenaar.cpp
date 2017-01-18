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

	controller.printToPlayer("welk karakter wil je vermoorden", gcon.getCurrentPlayer().get_name());

	for (std::shared_ptr<IKarakter> k : gcon.getKarakterCards().getDeck())
	{
		if (k->getName() != "Moordenaar")
		{
			controller.printToPlayer(std::to_string(counter) + " " + k->getName(), gcon.getCurrentPlayer().get_name());
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
			kill(gcon.getKarakterCards().getDeck().at(id - 1)->getName(), controller, gcon);
			controller.printToPlayer("je hebt de " + gcon.getKarakterCards().getDeck().at(id - 1)->getName() + " vermoord", gcon.getCurrentPlayer().get_name());
			a = true;
		}
		
	}

}

void Moordenaar::kill(std::string name, Controller & controller, GameController & gcon)
{
	for (std::shared_ptr<IKarakter> k : gcon.getKarakterCards().getDeck())
	{
		if (k->getName() == name)
		{
			k->setKilled(true);
		}
	}
}
