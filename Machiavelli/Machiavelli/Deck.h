#pragma once
#include <memory>
#include <vector>
#include <sstream>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>     
#include <time.h>
#include "IKarakter.h"
#include "Card.h"
#include "Moordenaar.h"
#include "Prediker.h"
#include "Magier.h"
#include "Koopman.h"
#include "Dief.h"
#include "Koning.h"
#include "Condottiere.h"
#include "Bouwmeester.h"


template <typename T>
class Deck {
public:
	Deck<T>::Deck()
	{
	}

	Deck<T>::~Deck()
	{
	}

	T Deck<T>::drawCard()
	{
		T c = std::move(_deck.back());
		_deck.pop_back();

		return c;
	}

	std::vector<T> getDeck() {
		return _deck;
	}

	void Deck<T>::CreateCardDeck()
	{
		//need random seed
		srand(time(NULL));
		while (_filestrings.size() > 0)
		{
			//select string from stream output vector
			int id = rand() % _filestrings.size();
			std::string output = _filestrings[id];

			//parsing/ placing back the whitespaces
			output = replaceChar(output, '_', ' ');
			std::vector<std::string> stringparts = splitString(output, ';');

			//create pointer, move pointer to deck
			std::unique_ptr<Card> card{ new Card(stringparts[0], stringparts[2], std::stoi(stringparts[1])) };
			_deck.push_back(std::move(card));

			//remove used string from output vector
			_filestrings.erase(_filestrings.begin() + id);
		}
	}

	void Deck<T>::CreateIKarakterDeck()
	{
		//need random seed
		srand(time(NULL));
		while (_filestrings.size() > 0)
		{
			//select string from stream output vector
			int id = rand() % _filestrings.size();
			std::string output = _filestrings[id];

			//parse string / get id for karakter card
			std::vector<std::string> stringparts = splitString(output, ';');			
			int karakterid = std::stoi(stringparts[0]);
			
			//we use the id of the karakter instead of the name, because you cant use a string for a switch.
			switch (karakterid)
			{
			case 1: {std::unique_ptr<IKarakter> m{ new Moordenaar };
					_deck.push_back(std::move(m)); }
					 break;
			case 2: {std::unique_ptr<IKarakter> d{ new Dief };
					_deck.push_back(std::move(d)); }
					 break;
			case(3) : {std::unique_ptr<IKarakter> a{ new Magier };
					  _deck.push_back(std::move(a)); }
					 break;
			case(4) : {std::unique_ptr<IKarakter> k{ new Koning };
					  _deck.push_back(std::move(k)); }
					 break;
			case(5) : {std::unique_ptr<IKarakter> p{ new Prediker };
					  _deck.push_back(std::move(p)); }
					 break;
			case(6) : {std::unique_ptr<IKarakter> o{ new Koopman };
					  _deck.push_back(std::move(o)); }
					 break;
			case(7) : {std::unique_ptr<IKarakter> b{ new Bouwmeester };
					  _deck.push_back(std::move(b)); }
					 break;
			case(8) : {std::unique_ptr<IKarakter> c{ new Condottiere };
					  _deck.push_back(std::move(c)); }
					 break;
			}
			
			//remove used string from output vector
			_filestrings.erase(_filestrings.begin() + id);
		}
	}

private:
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