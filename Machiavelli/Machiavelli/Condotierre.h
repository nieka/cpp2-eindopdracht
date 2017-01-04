#pragma once
#include "IKarakter.h"
class Condotierre :
	public IKarakter
{
public:
	Condotierre();
	~Condotierre();

	void play(Controller controller) override;
};

