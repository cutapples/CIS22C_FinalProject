#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "BST.h"
#include "HashTable.h"
#include "Database.h"
#include "SmashHero.h"

using namespace std;

void displayLoadingScreen();
void displayMainMenu();

void battleMenu(Database<SmashHero*>& database, bool battleHelp);
void purchaseMenu(Database<SmashHero*>& database);
void sellMenu(Database<SmashHero*>& database);
void heroListMenu(Database<SmashHero*>& database);
void teamMenu(Database<SmashHero*>& database);
void optionsMenu(Database<SmashHero*>& database);

int main() {

	displayLoadingScreen();
	fstream saveFile("SaveFile.txt");
	if (saveFile.fail()) {
		cout << "Error: Save file not found.\nCreating empty save file.\n";
		saveFile.close();
		saveFile.open("SaveFile.txt", ios::out);
		saveFile.close();
		saveFile.open("SaveFile.txt");
		cout << "Empty save file created.\n";
	}
	cout << "Initializing database...\n";
	Database<SmashHero*> database(saveFile);
	cout << "Database successfully intialized.\n";

	system("pause");

	bool ExitMainMenu = false;

	srand(time(NULL)); //creates a randomized seed for use in the Battle feature.

	bool battleHelp = true;

	do {
		system("cls");

		displayMainMenu();

		int userChoice;

		cin >> userChoice;

		switch (userChoice) {
		case 1:
			battleMenu(database, battleHelp);
			break;
		case 2:
			purchaseMenu(database);
			break;
		case 3:
			sellMenu(database);
			break;
		case 4:
			heroListMenu(database);
			break;
		case 5:	
			teamMenu(database);
			break;
		case 6:
			optionsMenu(database);
			break;
		case 7:
			ExitMainMenu = true;
			break;
		default:
			break;
		}

		system("pause");
		system("cls");

	} while (!ExitMainMenu);


	return 0;
}


void displayLoadingScreen() {
	cout << "===================Smash Heroes==================\n";
	cout << "Loading...\n";
	cout << "Loading SaveFile.txt...\n";
}

void displayMainMenu() {
	cout << "====================Main Menu====================" << endl;
	cout << "1. To Battle!" << endl;
	cout << "2. Purchase New Hero" << endl;
	cout << "3. Sell Hero" << endl;
	cout << "4. Hero List" << endl;
	cout << "5. Team Menu" << endl;
	cout << "6. Options Menu" << endl;
	cout << "7. Exit Game" << endl << endl;
}

void battleMenu(Database<SmashHero*>& database, bool battleHelp)
{
	system("cls");
	int choice = 0;
	cout << "====================Battle Menu====================" << endl;
	if (battleHelp == true)
	{
		cout << "\t\tHere is an explanation of the various systems at work here:" << endl;
		cout << "-Battles go automatically with no need for user input." << endl;
		cout << "-Both your party and a random enemy party are assigned a turn order for each member so everyone gets a turn." << endl;
		cout << "-When member A attacks member B, B's DEF stat is subtracted from A's ATK stat to get the final ATK stat." << endl;
		cout << "-Attacks have a base chance to miss." << endl;
		cout << "-If member B's DEF stat is higher than A's ATK stat, A's ATK stat will be set to a base minimum that scales with B's level." << endl;
		cout << "-When HP goes to 0, that member is knocked out. You can pay to heal up your current team back in the Main Menu." << endl;
		cout << "-You win by knocking out the entire enemy team and lose when your entire team gets knocked out. You earn gold and EXP regardless of win or lost." << endl;
		cout << "-You have a chance to randomly increase your earnings of gold and EXP." << endl;
		cout << "-If EXP >= 100, then you level up. You gain base stat increases (ATK+) as well as a random chance for more stat increases (ATK+ and DEF+++)." << endl;
		system("PAUSE");
		cout << endl << "\tWhat would you like to do?" << endl;
		cout << "1. I would like to battle an opponent" << endl;
		cout << "2. Back out to Main menu" << endl;
		cout << ">>> ";
		cin >> choice;
		if (choice == 1)
		{
			battleHelp = false;
			database.teamBattle();
		}
	}
	else
	{
		bool exit = false;
		do
		{
			cout << endl << "\tWhat would you like to do?" << endl;
			cout << "1. I would like to battle an opponent" << endl;
			cout << "2. View the Help screen again" << endl;
			cout << "3. Back out to Main Menu" << endl;
			cout << ">>> ";
			cin >> choice;
			switch (choice)
			{
			case 1:
				database.teamBattle();
				exit = true;
				break;
			case 2:
				cout << "\t\tHere is an explanation of the various systems at work here:" << endl;
				cout << "-Battles go automatically with no need for user input." << endl;
				cout << "-Both your party and a random enemy party are assigned a turn order for each member so everyone gets a turn." << endl;
				cout << "-When member A attacks member B, B's DEF stat is subtracted from A's ATK stat to get the final ATK stat." << endl;
				cout << "-Attacks have a base chance to miss." << endl;
				cout << "-If member B's DEF stat is higher than A's ATK stat, A's ATK stat will be set to a base minimum that scales with B's level." << endl;
				cout << "-When HP goes to 0, that member is knocked out. You can pay to heal up your current team back in the Main Menu." << endl;
				cout << "-You win by knocking out the entire enemy team and lose when your entire team gets knocked out. You earn gold and EXP regardless of win or lost." << endl;
				cout << "-You have a chance to randomly increase your earnings of gold and EXP." << endl;
				cout << "-If EXP >= 100, then you level up. You gain base stat increases (ATK+) as well as a random chance for more stat increases (ATK+ and DEF+++)." << endl;
				system("PAUSE");
				break;
			case 3:
				exit = true;
				break;
			default:
				cout << "Invalid input. Try again." << endl;
				break;
			}
		} while (!exit);
	}
}

/*
Purchase New Hero Menu

Show current gold and how much is to be subtracted
use Database::purchaseNewHero(int goldCost) to create and insert the new hero which returns back a pointer to be used
Display the new hero
*/
void purchaseMenu(Database<SmashHero*>& database) {

}

/*
Sell Menu
Prompt user for a primary key to be deleted
use Database::displayHero(int primaryKey)
Confirm delete
use Database::sellHero(int primaryKey)
*/
void sellMenu(Database<SmashHero*>& database) {

}

/*
Hero List Menu
HashTable inSequence function call
*/
void heroListMenu(Database<SmashHero*>& database) {

}

/*
Team List Menu

Display Team function call
Prompt user for which slot they want to replace
Prompt user for a primary key they own to be put into that slot
Swap Team Member function call
*/
void teamMenu(Database<SmashHero*>& database) {
	database.displayTeam();
	cout << "\nWhich slot would you like to swap?(6 for exit)";
	int slotChoice;
	cin >> slotChoice;
	if (slotChoice >= 6 || slotChoice <= 0) {
		return;
	}
	cout << "\nWhat hero would you like to put in slot " << slotChoice << "?(Enter hero key) ";
	int swapKey;
	cin >> swapKey;
	cout << "\n\nYou swapped in this hero into slot " << slotChoice << "!\n";
	database.displayHero(swapKey);
	database.swapTeamMember(slotChoice, swapKey);
}

/*
Options Menu
Extra menu options for project requirements
*/
void optionsMenu(Database<SmashHero*>& database) {

}
