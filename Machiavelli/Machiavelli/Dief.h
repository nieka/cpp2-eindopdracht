#pragma once
#include "IKarakter.h"
#include "Controller.h"

class Dief :
	public IKarakter
{
public:
	Dief();
	~Dief();

	void play(Controller controller);
};