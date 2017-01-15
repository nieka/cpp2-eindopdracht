#pragma once
#include "IKarakter.h"
#include "Controller.h"

class Bouwmeester :
public IKarakter
{
public:
	Bouwmeester();
	~Bouwmeester();

	void play(Controller controller);
};

