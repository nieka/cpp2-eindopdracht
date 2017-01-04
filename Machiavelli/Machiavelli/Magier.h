#pragma once
#include "IKarakter.h"
class Magier :
	public IKarakter
{
public:
	Magier();
	~Magier();

	void play(Controller controller) override;
};

