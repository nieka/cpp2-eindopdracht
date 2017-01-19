#pragma once
#include "IKarakter.h"
#include <vector>

class GameController;

class Moordenaar :
	public IKarakter
{
public:
	Moordenaar();
	~Moordenaar();
	void karakterInfo(Controller & controller, GameController & gcon);
	bool play(int input, Controller & controller, GameController & gcon);
private:
	void kill(std::string name, Controller & controller, GameController & gcon);
	std::vector<std::string> _names;
};