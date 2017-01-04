#pragma once
#include "IKarakter.h"
class Moordenaar :
	public IKarakter
{
public:
	Moordenaar();
	~Moordenaar();

	void play(Controller controller) override;
};

