#pragma once
#include "IKarakter.h"
class Koopman :
	public IKarakter
{
public:
	Koopman();
	~Koopman();

	void play(Controller controller) override;
};

