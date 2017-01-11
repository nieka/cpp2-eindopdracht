#include "Deck.h"

Deck::Deck()
{
}


Deck::~Deck()
{
}
/*
void Deck::addCard(std::unique_ptr<Card> c)
{
	_deck.push(std::move(c));
}

std::unique_ptr<Card> Deck::drawCard()
{
	std::unique_ptr<Card> card = std::move(_deck.front());
	_deck.pop();

	return std::move(card);
}
*/
void Deck::fillDeck()
{
	//test vector
	std::vector<Card> cards;

	std::ifstream file("Bouwkaarten.csv");
	std::string value;

	while (file.good())
	{
		std::getline(file, value, ',');
		//std::cout << value << std::endl;


		//TODO: parser om de data van de kaarten te scheiden.
	}
}

