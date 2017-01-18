#pragma once
#include "IKarakter.h"

class GameController;

class Bouwmeester :
public IKarakter
{
public:
	Bouwmeester();
	~Bouwmeester();

	void play(Controller & controller, GameController & gcon);
};

