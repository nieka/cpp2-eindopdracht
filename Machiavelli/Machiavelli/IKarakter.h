#pragma once
#include "Controller.h"

class IKarakter
{
public:
	IKarakter() {};
	~IKarakter() {};
	virtual void play(Controller controller) = 0;

	//getters
	bool getKilled();

	//setters
	void setKilled(bool k);
private:
	bool _Killed = false;
};