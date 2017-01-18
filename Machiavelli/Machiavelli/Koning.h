#pragma once
#include "IKarakter.h"

class GameController;

class Koning :
	public IKarakter
{
public:
	Koning();
	~Koning();

	void play(Controller & controller, GameController & gcon);
};