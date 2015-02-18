#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "Monster.h"
#include "Player.h"


Monster::Monster(string mname, int health)
{
	this->mname = mname;
	this->health = health;
}

string Monster::get_mname() {
	return mname;
}


int Monster::get_health() {
	return health;
}

void Monster::update_health(int new_health){
	health = new_health;
}

bool Monster::alive(){
	if (health <= 0)
		return false;
	else
		return true;
}

int Monster::attack(int mdamage){ // Random calculator to calculate monster's damage
	int x = rand() % 5;
	int y = rand() % 10;
	mdamage = x + y;
	return mdamage;
}

void Monster::reset(){ //Reset Monster with new Health
	health = rand() % (50 - 15) + 15;
}