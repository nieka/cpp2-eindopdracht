#pragma once
#include <string>
class Controller;
class GameController;

class IKarakter
{
public:
	IKarakter() {};
	~IKarakter() {};
	virtual bool play(int input, Controller & controller, GameController & gcon) = 0;
	virtual void karakterInfo(Controller & controller, GameController & gcon) = 0;

	//getters
	bool getKilled() const { return _Killed; };
	bool getTarget() const { return _target; };
	bool isOmgekeerd() const { return _omgekeerd; };
	std::string getName() const { return _name; };

	//setters
	void setKilled(bool k) { _Killed = k; };
	void setTarget(bool t) { _target = t; };
	void setOmgekeerd(bool o) { _omgekeerd = o; };

protected:
	bool _Killed = false; //moordenaar
	bool _target = false; //dief
	bool _omgekeerd = false; //is true als de kaart omgekeerd ligt
	std::string _name;
};