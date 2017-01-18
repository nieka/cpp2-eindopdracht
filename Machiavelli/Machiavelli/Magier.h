#pragma once
#include "IKarakter.h"

class GameController;

class Magier :
	public IKarakter
{
public:
	Magier();
	~Magier();

	void play(Controller & controller, GameController & gcon);
};