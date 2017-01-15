#pragma once
#include "IKarakter.h"

class Condottiere :
	public IKarakter
{
public:
	Condottiere();
	~Condottiere();

	void play(Controller controller);
};