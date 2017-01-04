#include "Card.h"

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
