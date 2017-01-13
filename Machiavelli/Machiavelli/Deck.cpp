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

/*
std::unique_ptr<Card> Deck::drawCard()
{
	std::unique_ptr<Card> card = std::move(_deck.front());
	_deck.pop();

	return std::move(card);
}
*/


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



