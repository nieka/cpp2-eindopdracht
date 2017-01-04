#pragma once
#include "Controller.h"

class IKarakter
{
public:
	IKarakter() {};
	~IKarakter() {};

	virtual void play(Controller controller) = 0;
};