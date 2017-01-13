#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <algorithm>
#include "Card.h"

class Deck
{
public:
	Deck();
	~Deck();
	void addCard(Card card);
	//std::unique_ptr<Card> drawCard();	
	friend std::ifstream& operator >> (std::ifstream& is, Deck& deck);
private:
	std::string  replaceChar(std::string s, char a, char b);
	std::vector<std::string> splitString(std::string s, char delimiter);
	//std::queue<std::unique_ptr<Card>> _deck;
	std::vector<Card> cardCollection;
};

