#pragma once
#include <string>
class Controller;

class IKarakter
{
public:
	IKarakter() {};
	~IKarakter() {};
	virtual void play(Controller controller) = 0;

	//getters
	bool getKilled() const
	{
		return _Killed;
	};
	std::string getName() const { return _name; }

	//setters
	void setKilled(bool k)
	{
		_Killed = k;
	};

protected:
	bool _Killed = false;
	std::string _name;
};