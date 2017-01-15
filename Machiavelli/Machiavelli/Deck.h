#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>     
#include <time.h>
#include "Card.h"
#include "IKarakter.h"

template <typename T>
class Deck {
public:
	Deck<T>::Deck()
	{
	}

	Deck<T>::~Deck()
	{
	}

	//T Deck<T>::drawCard()
	//{
	//	T c = _deck.back();
	//	_deck.pop_back();

	//	return c;
	//}

	void Deck<T>::addCard(T & t)
	{
		cardCollection.push_back(t);
	}

	void Deck<T>::shuffleDeck()
	{
		std::vector<T> newDeck;

		srand(time(NULL));
		while (cardCollection.size() > 0)
		{
			int id = rand() % cardCollection.size();
			newDeck.push_back(cardCollection[id]);
			cardCollection.erase(cardCollection.begin() + id);
		}

		_deck = newDeck;
	}

	void Deck<T>::CreateCardDeck()
	{
		for (std::string output : _filestrings)
		{
			
			output = replaceChar(output, '_', ' ');
			std::vector<std::string> stringparts = splitString(output, ';');

			Card card(stringparts[0], stringparts[2], std::stoi(stringparts[1]));
			addCard(card);
		}
	}

	void Deck<T>::CreateIKarakterDeck()
	{
		for (std::string output : _filestrings)
		{
			std::vector<std::string> stringparts = splitString(output, ';');
			
			//int id = std::stoi(stringparts[0]);
		}
	}

private:
	std::vector<T> cardCollection;
	std::vector<T> _deck;
	std::vector<std::string> _filestrings;

	//replace char a for char b in string s
	std::string  Deck<T>::replaceChar(std::string s, char a, char b)
	{
		std::replace(s.begin(), s.end(), a, b);
		return s;
	}

	//split the string into pieces and put them in a vector
	std::vector<std::string> Deck<T>::splitString(std::string s, char delimiter)
	{
		std::vector<std::string> i;
		std::stringstream ss(s); // Turn the string into a stream.
		std::string tok;

		while (getline(ss, tok, delimiter)) {
			i.push_back(tok);
		}

		return i;
	}

	void Deck<T>::addString(std::string s)
	{
		_filestrings.push_back(s);
	}

	//stream operator, reads file, place strings in filestring vector
	friend std::ifstream& operator >> (std::ifstream& is, Deck<T>& deck)
	{
		std::string output;

		is >> output;
		
		if (output.size() > 0)
		{
			deck.addString(output);
		}
		
		return is;
	}
};