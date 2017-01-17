#pragma once
#include "IKarakter.h"

class Dief :
	public IKarakter
{
public:
	Dief();
	~Dief();

	void play(Controller & controller);
};