#pragma once
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

	//setters
	void setKilled(bool k)
	{
		_Killed = k;
	};

private:
	bool _Killed = false;
};