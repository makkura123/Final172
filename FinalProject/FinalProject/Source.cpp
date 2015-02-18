#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "Player.h"
#include "Monster.h"

void save_game();
void load_game();

Player player1("name", 100, 1, 0); // Initializing Player Character with 100 health, level 1 and 0 money
Monster monster1("Goblin", 20); // Initializing first monster with 20 health

int main() {
	string pname;
	string choice;
	srand(time(0));
	int total = 0;

	string Buy;
	int item_gain = 0;
	int new_money = 0;

	// Display welcome message and let player set a name
	cout << "Welcome to Fight Simulator" << endl;
	cout << "What is your name? ";
	cin >> pname;
	player1.set_name(pname);
	cout << player1.get_name() << ", enjoy the game.\n" << endl;

	do {
		// Display menu of options
		cout << "Please select what you would like to do " << endl;
		cout << "1. Player Information\n";
		cout << "2. Train Character\n";
		cout << "3. Enter Item Shop\n";
		cout << "4. Use an Item\n";
		cout << "5. Save Game (Output file: SaveGame.txt)\n";
		cout << "6. Load Game (Input file: SaveGame.txt)\n";
		cout << "7. Quit\n";
		cout << "Select an option: ";

		// Read user selected option
		int select;
		cin >> select;

		// Decide what to do based on the user selected option
		switch (select) {
		case 1:	// Display player info
			cout << "Name: " << player1.get_name() << endl;
			cout << "Health: " << player1.get_health() << endl;
			cout << "Level: " << player1.get_level() << endl;
			cout << "Money: " << player1.get_money() << endl;
			break;

		case 2:	{// Train
					int random = player1.fight(total); // Making the fight damage a new variable, so that it doesn't have different values in cout and new_health
					int mdamage = 0;
					if (player1.alive() == true){ // Check if player is alive and start fight if yes

						cout << "A wild " << monster1.get_mname() <<" with " << monster1.get_health() << " health attacks." << endl;
						cout << player1.get_name() << " did " << random << " damage" << endl;
						monster1.update_health(monster1.get_health() - random); // Changes Health of monster depending on damage done
						while (monster1.get_health() > 0 && player1.alive() == true) { // start while loop for case that monster has 0 or more hp and player is alive
							cout << "Do you want to attack again? (Yes/No)" << endl;
							cin >> choice;
							if (choice == "Yes"){ //If player wants to attack again, repeat attack with new damage value

								random = player1.fight(total);
								monster1.update_health(monster1.get_health() - random);
								player1.update_health(player1.get_health() - monster1.attack(mdamage)); //Monster damages player
								cout << "Your health after Monster's attack: " << player1.get_health() << endl;
								cout << player1.get_name() << " did " << random << " damage" << endl;
							}

							else  if (choice == "No") // Option to run away from combat.
							{
								cout << "Monster did a final blow." << endl;
								player1.update_health(player1.get_health() - monster1.attack(mdamage)); //Monster damages player before he runs away
								cout << player1.get_name() << " fled the combat with " << player1.get_health() << " Health left." << endl;
								monster1.reset();
								break;
							}
							else
								cout << "Invalid option, please type Yes or No" << endl;
						}
						if (monster1.get_health() <= 0) // If monster has less than 0 HP, monster dies
						{
							cout << "Monster died" << endl;
							int rndgold = rand() % (15 - 5) + 5;
							int rndexp = rand() % (30 - 10) + 10;
							cout << "Player gained " << rndexp << " exp and " << rndgold << "gold" << endl; //Give exp and Gold
							player1.update_money(player1.get_money() + rndgold); // Update players money
							cout << player1.get_money() << endl;
						}
					}
					else
						cout << "You died, please use a PhoenixFeather" << endl;

					monster1.reset();
					break;
		}

		case 3:{ // Shop
				   vector<string> items;	// Vector to contain Item names
				   vector <int> use; // Vector to contain the health/damage difference that item does;
				   vector <int> cost; // Vector to contain the cost values
				   string item_name;
				   int item_number, item_cost;
				   ifstream fin;

				   cout << "Welcome to the Item Shop!\n";
				   cout << "You have " << player1.get_money() << " gold.\n";
				   cout << "Here's what we're selling: \n\n";

				   fin.open("Items.txt"); //Open Items.txt file

				   if (fin.fail()) { // If file cannot be opened, print
					   cout << "can't open file" << endl;
					   return 0;
				   }
				   while (!fin.eof()) { // Repeat while we have not yet reached the end-of-file
					   fin >> item_name;	//Read the item name from line
					   fin >> item_cost; // Read the cost of the items
					   fin >> item_number; // Read effect of items (heal/damage)
					   items.push_back(item_name);
					   cost.push_back(item_cost);
					   use.push_back(item_number);
				   }
				   fin.close(); //Close file

				   for (int i = 0; i < 10; i++){ //Print Itemlist with cost
					   cout << i + 1 << ". " << items[i] << " for " << cost[i] << " gold" << endl;
				   }

				   cout << endl << "What would you like to buy? (Enter the name of the item you wish to purchase or type 'exit' to leave)\n";
				   cin >> Buy; //Prompt player to choose item

				   for (int i = 0; i < 10; i++){
					   if (Buy == items[i]) // Check if item is in vector
					   {
						   if (player1.get_money() >= cost[i]) // Check if player has enough money
						   {
							   cout << items[i] << " bought." << endl;
							   player1.update_money(player1.get_money() - cost[i]); //Subtract cost from player money
							   item_gain = i + 1;
						   }
						   else
							   cout << "You can't afford " << items[i] << ", " << cost[i] - player1.get_money() << " missing." << endl;
					   }
					   else if (Buy == "exit") //Exit the shop
						   break;
					   else // Invalid Option
						   cout << "Item does not exist" << endl;
				   }
				   break;
		}

		case 4:{
				   vector<string> items;	// Vector to contain Item names
				   vector <int> use; // Vector to contain the health/damage difference that item does;
				   vector <int> cost; // Vector to contain the cost information
				   string item_name;
				   int item_number, item_cost;
				   ifstream fin;

				   fin.open("Items.txt");

				   if (fin.fail()) {
					   cout << "can't open file" << endl;
					   return 0;
				   }
				   while (!fin.eof()) { // Repeat while we have not yet reached the end-of-file
					   fin >> item_name;	//Read the item name from line
					   fin >> item_cost;
					   fin >> item_number;
					   items.push_back(item_name);
					   cost.push_back(item_cost);
					   use.push_back(item_number);
				   }
				   fin.close(); //Close file

				   if (item_gain == 1) // If item 1 was bought
				   {
					   cout << "You used a " << items[item_gain - 1] << " and healed yourself for " << use[item_gain - 1] << endl;
					   if (player1.get_health() + use[item_gain - 1] <= 100)
					   {
						   player1.update_health(player1.get_health() + use[item_gain - 1]);
					   }
					   else
						   player1.update_health(100);
					   cout << "Your health now: " << player1.get_health() << endl;
				   }

				   else  if (item_gain == 2) // If item 2 was bought
				   {
					   cout << "You used a " << items[item_gain - 1] << " and healed yourself for " << use[item_gain - 1] << endl;
					   if (player1.get_health() + use[item_gain - 1] <= 100)
					   {
						   player1.update_health(player1.get_health() + use[item_gain - 1]);
					   }
					   else
						   player1.update_health(100);
					   cout << "Your health now: " << player1.get_health() << endl;
				   }

				   else  if (item_gain == 3) // If item 3 was bought
				   {
					   cout << "You used a " << items[item_gain - 1] << " and healed yourself for " << use[item_gain - 1] << endl;
					   if (player1.get_health() + use[item_gain - 1] <= 100)
					   {
						   player1.update_health(player1.get_health() + use[item_gain - 1]);
					   }
					   else
						   player1.update_health(100);
					   cout << "Your health now: " << player1.get_health() << endl;
				   }

				   else  if (item_gain == 4) // If item 4 was bought
				   {
					   cout << "You used a " << items[item_gain - 1] << " and enhanced your next attack by " << use[item_gain - 1] << endl;
					   monster1.update_health(monster1.get_health() - use[item_gain - 1]);
				   }

				   else  if (item_gain == 5)// If item 5 was bought
				   {
					   cout << "You used a " << items[item_gain - 1] << " and enhanced your next attack by " << use[item_gain - 1] << endl;
					   monster1.update_health(monster1.get_health() - use[item_gain - 1]);
				   }

				   else  if (item_gain == 6)// If item 6 was bought
				   {
					   cout << "You used a " << items[item_gain - 1] << " and enhanced your next attack by " << use[item_gain - 1] << endl;
					   monster1.update_health(monster1.get_health() - use[item_gain - 1]);
				   }

				   else  if (item_gain == 7)// If item 7 was bought
				   {
					   cout << "You used a " << items[item_gain - 1] << " and increased your health by " << use[item_gain - 1] << endl;
					   player1.update_health(player1.get_health() + use[item_gain - 1]);
				   }

				   else  if (item_gain == 8)// If item 8 was bought
				   {
					   cout << "You used a " << items[item_gain - 1] << " and increased your health by " << use[item_gain - 1] << endl;
					   player1.update_health(player1.get_health() + use[item_gain - 1]);
				   }

				   else  if (item_gain == 9) // If item 9 was bought
				   {
					   if (player1.alive() == true)
					   {
						   cout << "You are already alive." << endl;
						   break;
					   }
					   else
					   {
						   cout << "You used a " << items[item_gain - 1] << " and resurrected yourself and are back to full health." << endl;
						   player1.update_health(100); //Revive player
					   }
				   }

				   else  if (item_gain == 10) // If item 10 was bought
				   {
					   int sodexo = rand() % (3 - 1) + 1; // Random Calculator for odds of item working
					   if (sodexo == 2)
					   {
						   cout << "You used a " << items[item_gain - 1] << " and, luckily, healed yourself by " << use[item_gain - 1] << endl;
						   player1.update_health(player1.get_health() + use[item_gain - 1]);
					   }
					   else if (sodexo == 1 || sodexo == 3)
					   {
						   cout << "You used a " << items[item_gain - 1] << ". Congratulations, you got food poisoning and lost " << use[item_gain - 1] << "health" << endl;
						   player1.update_health(player1.get_health() - use[item_gain - 1]);
					   }
				   }

				   item_gain = 0;
				   break;
		}

		case 5:	// Save game log into the file GameLog.txt
			cout << "Saving to Gamelog.txt ...\n";
			save_game();
			break;

		case 6:	// Load gamefile from GameLog.txt
			load_game();
			break;

		case 7:	// Quit
			cout << "Goodbye\n";
			return 0;

		default: // Invalid option entry
			cout << select << " is not a valid option.  Please try again\n";
			break;
		}
		cin.ignore();
		cout << "Press enter to continue\n";
		cin.get();
		system("cls");
	} while (true);
}

void save_game(){ // Function for saving the game
	string outfile = "GameLog.txt";
	ofstream fout(outfile, ios::app); // open file and allow to add more than one entry
	if (fout.fail()){
		cout << "Fail to open" << outfile << endl;
		return;
	}
	fout << player1.get_name() << " " << player1.get_health();
	fout << " " << player1.get_level() << " " << player1.get_money() << endl;

	fout.close();
}


void load_game(){ // Function for loading the game
	string name;
	int health, level, money;

	ifstream fin;
	fin.open("GameLog.txt");

	if (fin.fail()){
		cout << "No saved game" << endl;
		return;
	}

	while (!fin.eof()){
		fin >> name;
		fin >> health;
		fin >> level;
		fin >> money;
	}
	player1.set_name(name);
	player1.update_health(health);
	player1.update_money(money);
}