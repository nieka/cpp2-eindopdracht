#pragma once
#include "IKarakter.h"

class Prediker :
	public IKarakter
{
public:
	Prediker();
	~Prediker();

	void play(Controller & controller);
};