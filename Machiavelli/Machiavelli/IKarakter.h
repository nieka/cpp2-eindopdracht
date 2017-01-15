#pragma once
#include "Controller.h"

class Controller;

class IKarakter
{
public:
	IKarakter() {};
	~IKarakter() {};
	virtual void play(Controller controller) = 0;

	//getters
	bool getKilled()
	{
		return _Killed;
	};

	//setters
	void setKilled(bool k)
	{
		_Killed = k;
	};

private:
	bool _Killed = false;
};