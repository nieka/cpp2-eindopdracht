#pragma once
#include "IKarakter.h"

class GameController;

class Prediker :
	public IKarakter
{
public:
	Prediker();
	~Prediker();

	void karakterInfo(Controller & controller, GameController & gcon);
	bool play(int input, Controller & controller, GameController & gcon);
};