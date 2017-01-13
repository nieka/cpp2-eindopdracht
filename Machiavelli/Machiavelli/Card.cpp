#include "Card.h"

Card::Card()
{
}

Card::~Card()
{
}

std::string Card::getName() const
{
	return _name;
}

std::string Card::getColor() const
{
	return _color;
}

int Card::getWaarde() const
{
	return _waarde;
}

void Card::setName(std::string n)
{
	_name = n;
}

void Card::setColor(std::string c)
{
	_color = c;
}

void Card::setwaarde(int w)
{
	_waarde = w;
}
