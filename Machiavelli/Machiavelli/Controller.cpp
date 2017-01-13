#include "Controller.h"

Controller::Controller()
{
	createDeck("Bouwkaarten.csv");
}


Controller::~Controller()
{
}

void Controller::handleCommand(ClientCommand command)
{
	//todo handle commands

}

void Controller::createDeck(std::string filepath)
{
	std::ifstream file(filepath);

	while (file.good())
	{
		file >> deck;
	}
	file.close();

	deck.shuffleDeck();
}
