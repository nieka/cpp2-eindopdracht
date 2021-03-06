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
#include "IKarakter.h"

class GameController;

class Player {
public:
	Player() { _firstTomaxBuildings = false; }
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
	const bool isKoning() const;

	int calculateScore();
	void setFirstToMaxBuildeings();
	void resetRound();

	void AddBouwCard(std::shared_ptr<Card> card);
	void AddKarakterKaart(std::shared_ptr<IKarakter> card);
	void bouwGebouw(std::shared_ptr<Card> card);
	void verwijderGebouw(int id);
	void verwijderGebouwkaart(std::shared_ptr<Card> card);
	const bool hasKarakterKaart(std::string name);
	std::vector<std::shared_ptr<Card>> getBouwKaarten() const;
	std::vector<std::shared_ptr<Card>> & getGebouwdeKaarten();
	void setBouwkaarten(std::vector<std::shared_ptr<Card>> cards);
private:
    std::string name;
	int age; 
	int _goudstukken;
	//pointers required for inheritance of the karakter cards
	std::vector<std::shared_ptr<Card>> _bouwKaarten;
	std::vector<std::shared_ptr<IKarakter>> _karakterKaarten;
	std::vector<std::shared_ptr<Card>> _gebouwdeKaarten;
	bool _koning = false;
	bool _firstTomaxBuildings = false;
};

#endif /* Player_hpp */
