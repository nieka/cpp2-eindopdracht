#pragma once
#include "IKarakter.h"

class GameController;

class Dief :
	public IKarakter
{
public:
	Dief();
	~Dief();

	void play(Controller & controller, GameController & gcon);
};