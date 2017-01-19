#pragma once
#include "IKarakter.h"

class GameController;

class Condottiere :
	public IKarakter
{
public:
	Condottiere();
	~Condottiere();

	void karakterInfo(Controller & controller, GameController & gcon);
	bool play(int input, Controller & controller, GameController & gcon);
};