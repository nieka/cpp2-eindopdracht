#pragma once
//kan queue en memory niet gebruiken, hebben conflicten met de std queue's in de main
//#include <queue>
//#include <memory>
#include <vector>
#include <fstream>
#include <Iostream>
#include <string>
#include "Card.h"

class Deck
{
public:
	Deck();
	~Deck();
	//void addCard(std::unique_ptr<Card> c);
	//std::unique_ptr<Card> drawCard();
	void fillDeck();
private:
	//std::queue<std::unique_ptr<Card>> _deck;
};

