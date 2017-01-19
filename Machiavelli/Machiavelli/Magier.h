#pragma once
#include "IKarakter.h"

class GameController;

class Magier :
	public IKarakter
{
public:
	Magier();
	~Magier();

	void karakterInfo(Controller & controller, GameController & gcon);
	bool play(int input, Controller & controller, GameController & gcon);
};