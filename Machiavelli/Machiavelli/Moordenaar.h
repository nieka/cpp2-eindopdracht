#pragma once
#include "IKarakter.h"

class GameController;

class Moordenaar :
	public IKarakter
{
public:
	Moordenaar();
	~Moordenaar();

	void play(Controller & controller, GameController & gcon);
private:
	void kill(std::string name, Controller & controller, GameController & gcon);
};