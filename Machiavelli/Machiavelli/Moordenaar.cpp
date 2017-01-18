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
		switch (id)
		{
		case(1):
			kill("Magier", controller, gcon);
			controller.printToPlayer("je vermoord 1", gcon.getCurrentPlayer().get_name());
			a = true;
			break;
		case(2):
			kill("Dief", controller, gcon);
			controller.printToPlayer("je vermoord 2", gcon.getCurrentPlayer().get_name());
			a = true;
			break;
		case(3):
			kill("Bouwmeester", controller, gcon);
			controller.printToPlayer("je vermoord 3", gcon.getCurrentPlayer().get_name());
			a = true;
			break;
		case(4):
			kill("Koopman", controller, gcon);
			controller.printToPlayer("je vermoord 4", gcon.getCurrentPlayer().get_name());
			a = true;
			break;
		case(5):
			kill("Condottiere", controller, gcon);
			controller.printToPlayer("je vermoord 5", gcon.getCurrentPlayer().get_name());
			a = true;
			break;
		case(6):
			kill("Koning", controller, gcon);
			controller.printToPlayer("je vermoord 6", gcon.getCurrentPlayer().get_name());
			a = true;
			break;
		default:
			controller.printToPlayer("enter a number from the list", gcon.getCurrentPlayer().get_name());
			break;
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
