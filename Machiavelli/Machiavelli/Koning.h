#pragma once
#include "IKarakter.h"
class Koning :
	public IKarakter
{
public:
	Koning();
	~Koning();

	void play(Controller controller) override;
};

