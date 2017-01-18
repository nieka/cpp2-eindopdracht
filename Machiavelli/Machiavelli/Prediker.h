#pragma once
#include "IKarakter.h"

class GameController;

class Prediker :
	public IKarakter
{
public:
	Prediker();
	~Prediker();

	void play(Controller & controller, GameController & gcon);
};