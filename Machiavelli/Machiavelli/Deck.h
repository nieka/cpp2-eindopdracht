#pragma once
//kan queue en memory niet gebruiken, hebben conflicten met de std queue's in de main

//#include <memory>
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

class Deck
{
public:
	Deck();
	~Deck();
	void addCard(Card card);
	Card drawCard();	
	friend std::ifstream& operator >> (std::ifstream& is, Deck& deck);
	void shuffleDeck();
private:
	std::string  replaceChar(std::string s, char a, char b);
	std::vector<std::string> splitString(std::string s, char delimiter);
	std::vector<Card> cardCollection;
	std::vector<Card> _deck;
};

