#pragma once
#include "IKarakter.h"
#include "Controller.h"

class Moordenaar :
	public IKarakter
{
public:
	Moordenaar();
	~Moordenaar();

	void play(Controller controller);
};