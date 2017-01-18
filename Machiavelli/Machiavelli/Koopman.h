#pragma once
#include "IKarakter.h"

class GameController;

class Koopman :
	public IKarakter
{
public:
	Koopman();
	~Koopman();

	void play(Controller & controller, GameController & gcon);
};