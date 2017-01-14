//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Card.h"

class Player {
public:
    Player() {}
	Player(const std::string& name, int age) : name{ name }, age{ age } {}
	~Player();

	//getter and setters
	std::string get_name() const;
	void set_name(const std::string& new_name);

	int getAge() const;
	void set_age(int new_age);

	int getGoudstukken() const;
	void addGoudStukken(int extre_goudstukken);
	void setGoudStukkken(int goudstukken);
	void setKoning(const bool koning);
	const bool isKoning();

	void drawCard();
	void showHand();
private:
    std::string name;
	int age; 
	int _goudstukken;
	std::vector<std::shared_ptr<Card>> _hand;
	bool _koning = false;
};

#endif /* Player_hpp */
