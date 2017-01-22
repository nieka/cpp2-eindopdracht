#pragma once
#include "IKarakter.h"
//#include <vector>

class GameController;

class Dief :
	public IKarakter
{
public:
	Dief();
	~Dief();

	void karakterInfo(Controller & controller, GameController & gcon);
	bool play(int input, Controller & controller, GameController & gcon);
private:
	//std::vector<std::string> _names;
};