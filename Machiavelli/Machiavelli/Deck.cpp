#include "Deck.h"

Deck::Deck()
{
}


Deck::~Deck()
{
}

void Deck::addCard(Card card)
{
	cardCollection.push_back(card);
}

Card Deck::drawCard()
{
	Card c = _deck.back();
	_deck.pop_back();

	return c;
}

//replace char a for char b in string s
std::string  Deck::replaceChar(std::string s, char a, char b)
{
	std::replace(s.begin(), s.end(), a, b);
	return s;
}

//split the string into pieces and put them in a vector
std::vector<std::string> Deck::splitString(std::string s, char delimiter)
{
	std::vector<std::string> internal;
	std::stringstream ss(s); // Turn the string into a stream.
	std::string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

void Deck::shuffleDeck()
{
	std::vector<Card> newDeck;

	srand(time(NULL));
	while (cardCollection.size() > 0)
	{
		int id = rand() % cardCollection.size();
		//std::cout << std::to_string(id) << std::endl;

		newDeck.push_back(cardCollection[id]);
		cardCollection.erase(cardCollection.begin() + id);
	}

	_deck = newDeck;
}

//stream operator, reads file, used to create the cards, and place them in the cardcollection vector
std::ifstream& operator >> (std::ifstream& is, Deck& deck)
{
	std::string output;

	is >> output;

	if (output.size() > 0)
	{
		output = deck.replaceChar(output, '_', ' ');
		std::vector<std::string> stringparts = deck.splitString(output, ';');

		Card card(stringparts[0], stringparts[2], std::stoi(stringparts[1]));
		deck.addCard(card);
	}

	return is;
}



