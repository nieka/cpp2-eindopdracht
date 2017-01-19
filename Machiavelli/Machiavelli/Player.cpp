//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.h"
#include <algorithm>
using namespace std;

Player::~Player()
{
}

std::string Player::get_name() const
{
	return name;
}

void Player::set_name(const std::string & new_name)
{
	name = new_name;
}

int Player::getAge() const
{
	return age;
}

void Player::set_age(int new_age)
{
	age = new_age;
}

int Player::getGoudstukken() const
{
	return _goudstukken;
}

void Player::addGoudStukken(int extre_goudstukken)
{
	_goudstukken += extre_goudstukken;
}

void Player::setGoudStukkken(int goudstukken)
{
	_goudstukken = goudstukken;
}

void Player::setKoning(const bool koning)
{
	_koning = koning;
}

const bool Player::isKoning()
{
	return _koning;
}

void Player::AddBouwCard(std::shared_ptr<Card> card)
{
	_bouwKaarten.push_back(card);
}

void Player::AddKarakterKaart(std::shared_ptr<IKarakter> card)
{
	_karakterKaarten.push_back(card);
}

void Player::bouwGebouw(std::shared_ptr<Card> card)
{
	_bouwKaarten.erase(std::remove(_bouwKaarten.begin(), _bouwKaarten.end(), card), _bouwKaarten.end());
	_gebouwdeKaarten.push_back(card);
}

const bool Player::hasKarakterKaart(const std::string name)
{
	bool hasCard = false;
	std::for_each(_karakterKaarten.begin(), _karakterKaarten.end(), [&](std::shared_ptr<IKarakter> card) { if (card->getName() == name) {
		hasCard = true;
	}
	});

	return hasCard;
}

void Player::playKarakterAbility(Controller & controller, std::string karakternaam)
{
	std::for_each(_karakterKaarten.begin(), _karakterKaarten.end(), [&](std::shared_ptr<IKarakter> card) { 
		if (card->getName() == karakternaam) {
			card->play(controller);
		}
	});
}

std::vector<std::shared_ptr<Card>> Player::getBouwKaarten() const
{
	return _bouwKaarten;
}

std::vector<std::shared_ptr<Card>> Player::getGebouwdeKaarten() const
{
	return _gebouwdeKaarten;
}
