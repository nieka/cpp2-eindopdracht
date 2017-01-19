#pragma once
#include "IKarakter.h"

class GameController;

class Koning :
	public IKarakter
{
public:
	Koning();
	~Koning();

	void karakterInfo(Controller & controller, GameController & gcon);
	bool play(int input, Controller & controller, GameController & gcon);
};