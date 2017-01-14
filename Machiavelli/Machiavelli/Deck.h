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

template <class T>
class Deck {
public:
	Deck();
	~Deck();
	void addCard(T& t);
	//T& drawCard();	
	void shuffleDeck();

	friend std::ifstream& operator >> (std::ifstream&, const Deck<T>&);
private:
	std::string  replaceChar(std::string s, char a, char b);
	std::vector<std::string> splitString(std::string s, char delimiter);
	std::vector<T> cardCollection;
	std::vector<T> _deck;
};