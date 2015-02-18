#ifndef _Player_H_
#define _Player_H_

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

	class Player
	{
	private:
		string name;
		int level;
		int health;
		int money;
	public:
		
		Player(string name, int health, int level, int money); // Constructor for initializing the properties of Player Object


		void set_name(string pname); //give player a name
		string get_name(); //return player's name
		int get_health(); // return player's health
		void update_health(int new_healthp); // update health
		int get_level(); // return player's level
		bool alive(); // check if player is alive
		int get_money(); // return player's money
		void update_money(int new_money); // update money

		int fight(int total); // allow player to fight
	};

#endif
