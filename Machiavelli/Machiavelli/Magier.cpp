#include "Magier.h"
#include "Controller.h"

Magier::Magier()
{
	_name = "Magier";
}


Magier::~Magier()
{
}

void Magier::karakterInfo(Controller & controller, GameController & gcon)
{
	controller.printToPlayer("Kies tussen de volgende opties:", gcon.getCurrentPlayer().get_name());
	controller.printToPlayer("type '100' om alle bouwkaarten te ruilen met de andere speler", gcon.getCurrentPlayer().get_name());
	controller.printToPlayer("type de id van de kaarten die je wilt afleggen voor nieuwe kaarten", gcon.getCurrentPlayer().get_name());

	int counter = 1;

	for (std::shared_ptr<Card> c : gcon.getCurrentPlayer().getBouwKaarten())
	{
		controller.printToPlayer(std::to_string(counter) + " " + c->getName() + " " + c->getColor(), gcon.getCurrentPlayer().get_name());
		++counter;
	}

}

bool Magier::play(int input, Controller & controller, GameController & gcon)
{
	if (input == 100)
	{
		std::vector<std::shared_ptr<Card>> speler1 = gcon.getPlayer1().getBouwKaarten();
		std::vector<std::shared_ptr<Card>> speler2 = gcon.getPlayer2().getBouwKaarten();
		gcon.getPlayer1().setBouwkaarten(speler2);
		gcon.getPlayer2().setBouwkaarten(speler1);
		controller.printLine("de magier gebruikt zijn ability om jullie bouwkaarten om te wisselen.");
		return true;
	}
	else
	{
		std::vector<std::shared_ptr<Card>> Cards = gcon.getCurrentPlayer().getBouwKaarten();
		std::vector<int> numbers;
		std::string in = std::to_string(input);
		int counter = 0;

		for (char a : in)
		{
			std::string b(1, a);
			int result = std::stoi(b);

			if (checknumber(numbers, result))
			{
				try
				{
					std::shared_ptr<Card> b{ Cards.at(result - 1) };
					gcon.getCurrentPlayer().verwijderGebouwkaart(b);
				}
				catch (...)
				{
					controller.printToPlayer("voor een id in van een kaart", gcon.getCurrentPlayer().get_name());
					return false;
				}

				numbers.push_back(result);
				counter++;
			}
			
			
		}

		for (int i = 0; i < counter; ++i)
		{
			std::shared_ptr<Card> newcard = gcon.getBouwKaarten().drawCard();
			controller.printToPlayer("de bouwkaart " + newcard->getName() + " " + newcard->getColor() + " is toegevoegd aan je hand.", gcon.getCurrentPlayer().get_name());
			gcon.getCurrentPlayer().AddBouwCard(std::move(newcard));
		}

		return true;
	}
		
}

bool Magier::checknumber(std::vector<int> numbers, int n)
{
	for (int i : numbers)
	{
		if (i == n)
		{
			return false;
		}
	}

	return true;
}
