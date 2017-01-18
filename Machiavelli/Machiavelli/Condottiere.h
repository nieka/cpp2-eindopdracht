#pragma once
#include "IKarakter.h"

class GameController;

class Condottiere :
	public IKarakter
{
public:
	Condottiere();
	~Condottiere();

	void play(Controller & controller, GameController & gcon);
};