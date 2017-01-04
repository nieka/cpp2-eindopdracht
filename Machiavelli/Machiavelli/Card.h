#pragma once
#include <iostream>
class Card
{
public:
	Card(std::string name, std::string color, int waarde) : _name{ name }, _color{ color }, _waarde{ waarde } {}
	~Card();

	//getters
	std::string getName() const;
	std::string getColor() const;
	int getWaarde() const;

protected:
	std::string _name;
	std::string _color;
	int _waarde;

};
