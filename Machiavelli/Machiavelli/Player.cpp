//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.h"
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
	return goudstukken;
}

void Player::addGoudStukken(int extre_goudstukken)
{
	goudstukken += extre_goudstukken;
}

void Player::drawCard()
{
}

void Player::showHand()
{
}
