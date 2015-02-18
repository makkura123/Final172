#ifndef _Monster_H_
#define _Monster_H_

#include "Player.h";

using namespace std;

class Monster
{
private:
	string mname;
	int health;
public:
	Monster(string mname, int health); // Constructor for initializing the properties of Player Object
																	

	string get_mname(); //return monster's name
	int get_health(); // return monster's health
	void update_health(int new_health); //update health
	bool alive(); //check if monster
	
	int attack(int mdamage); // Monster attacks
	void reset(); // Reset monster for next fight
};

#endif