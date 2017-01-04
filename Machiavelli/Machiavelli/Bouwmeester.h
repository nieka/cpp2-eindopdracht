#pragma once
#include "IKarakter.h"
class Bouwmeester :
	public IKarakter
{
public:
	Bouwmeester();
	~Bouwmeester();

	void play(Controller controller) override;
};

