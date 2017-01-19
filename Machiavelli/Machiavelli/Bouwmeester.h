#pragma once
#include "IKarakter.h"

class GameController;

class Bouwmeester :
public IKarakter
{
public:
	Bouwmeester();
	~Bouwmeester();

	void karakterInfo(Controller & controller, GameController & gcon);
	bool play(int input, Controller & controller, GameController & gcon);
};

