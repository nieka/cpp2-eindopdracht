#pragma once
#include <iostream>
#include <string>
class Card
{
public:
	Card(std::string name, std::string color, int waarde) : _name{ name }, _color{ color }, _waarde{ waarde } {}
	Card();
	~Card();

	//getters
	std::string getName() const;
	std::string getColor() const;
	int getWaarde() const;

	//setters
	void setName(std::string n);
	void setColor(std::string c);
	void setwaarde(int w);

protected:
	std::string _name;
	std::string _color;
	int _waarde;
};
