#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "Player.h"



Player::Player(string name, int health, int level, int money) //Constructor for player
{
	this->name = name;
	this->health = health;
	this->level = level;
	this->money = money;

}


string Player::get_name() {
	return name;
}

void Player::set_name(string pname){
	name = pname;
}

int Player::get_health() {
	return health;
}

int Player::get_level () {
	return level;
}

int Player::get_money() {
	return money;
}
void Player::update_money(int new_money){
	money = new_money;
}

int Player::fight(int total){ // Calculate player damage
		int x = rand() % 10;
		int y = rand() % 10;
		total = x + y;
		return total;
	}

void Player::update_health(int new_healthp){
	health = new_healthp;
}

bool Player::alive(){
	if (health <= 0)
		return false;
	else
		return true;
}
