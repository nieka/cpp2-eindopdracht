#pragma once
#include "IKarakter.h"

class GameController;

class Koopman :
	public IKarakter
{
public:
	Koopman();
	~Koopman();

	void karakterInfo(Controller & controller, GameController & gcon);
	bool play(int input, Controller & controller, GameController & gcon);
};