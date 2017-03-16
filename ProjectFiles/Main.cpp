#include <iostream>
#include <string>
#include <fstream>

#include "BST.h"
#include "HashTable.h"
#include "Database.h"
#include "SmashHero.h"

using namespace std;

void displayLoadingScreen();
void displayMainMenu();

void battleMenu(Database<SmashHero*>& database);
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

	do {
		system("cls");

		displayMainMenu();

		int userChoice;

		cin >> userChoice;

		switch (userChoice) {
		case 1:
			battleMenu(database);
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

/*
Battle Menu

Display the team on a special battle screen
use Database::teamBattle() to get the rewards
Display gold added and increased stats?
*/
void battleMenu(Database<SmashHero*>& database) 
{
						//Mental Map
	//Format: /t getPartyMember1 << "HP: " << getCurrentHealth << "/" << getMaxHealth << endl;
	//We autobattle for each turn. We pause the system for 2-3 secs(?) so as to not have the system display each turn instantaneously.
	//When we get each party member, we assign each a number 1-5 based on number of members in party. Enemy team will get 6-10.
	//Each turn we randomize int variable called OurTurnOrder(?) from 1-5 and then another variable called TheirTurnOrder from 6-10.

	//Dodge mechanic: int variable called dodgeChance will randomize 0-25 chance to miss and 26-100 to hit when the function is called in Database. Return 0 for miss and 1 for hit.
	//if statements for return value of 0 for miss and 1 for hit. If miss, do not call the attack function. If hit, call the attack function. 
	
	//Pass the TheirTurnOrder's getCurrentHealth to Attack function so the function knows the Attack function will randomize int variable 
	//AttackPower from 1 to getCurrentHealth. If balance issue occur, then 1 to getCurrentHealth - 2. Return int attack power.
	//either handle arithmetic operation getCurrentHealth - attackpower in main or create function in Database to handle it.
	//if statements to handle if result is negative or not. If < 0, either delete member from cout statements and stop calling its functions(?).

	/t	Party Member 1 HP: 10/10	/t Enemy Member 1 HP: 10/10
	/t	Party Member 2 HP: 12/12	/t Enemy Member 2 HP: 12/12
	/t	Party Member 3 HP: 15/15	/t Enemy Member 3 HP: 15/15
	Turn 1:
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
