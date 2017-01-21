#pragma once
#include "IKarakter.h"
#include <vector>

class GameController;

class Magier :
	public IKarakter
{
public:
	Magier();
	~Magier();

	void karakterInfo(Controller & controller, GameController & gcon);
	bool play(int input, Controller & controller, GameController & gcon);
private:
	bool checknumber(std::vector<int> numbers, int n);
};