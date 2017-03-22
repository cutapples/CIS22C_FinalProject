#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "HashTable.h"
#include "BST.h"
#include "SmashHero.h"
#include "Database.h"

using namespace std;

void displayLoadingScreen();
void displayMainMenu();

void battleMenu(Database<SmashHero>& database);
void purchaseMenu(Database<SmashHero>& database);
void sellMenu(Database<SmashHero>& database);
void heroListMenu(Database<SmashHero>& database);
void teamMenu(Database<SmashHero>& database);
void optionsMenu(Database<SmashHero>& database);

int main() 
{
	srand(time(0));		// use current time as seed.
	displayLoadingScreen();
	cout << "Initializing database...\n";
	Database<SmashHero> database;
	cout << "Database successfully intialized.\n\n";

	system("pause");
	bool ExitMainMenu = false;
	do {
		system("cls");
		displayMainMenu();
		int userChoice;
		cin >> userChoice;
		switch (userChoice) 
		{
		case 1:
			system("cls");
			battleMenu(database);
			break;
		case 2:
			system("cls");
			purchaseMenu(database);
			break;
		case 3:
			system("cls");
			sellMenu(database);
			break;
		case 4:
			system("cls");
			heroListMenu(database);
			break;
		case 5:	
			system("cls");
			teamMenu(database);
			break;
		case 6:
			system("cls");
			optionsMenu(database);
			break;
		case 7:
			ExitMainMenu = true;
			break;
		default:
			break;
		}
		system("pause");
	} while (!ExitMainMenu);
	return 0;
}

void displayLoadingScreen() 
{
	cout << "===================Smash Heroes==================\n";
	cout << "Loading...\n";
	cout << "Loading SaveFile.txt...\n";
}

void displayMainMenu() 
{
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
void battleMenu(Database<SmashHero>& database) 
{
	database.teamBattle();
}

/*
Purchase New Hero Menu

Show current gold and how much is to be subtracted
use Database::purchaseNewHero(int goldCost) to create and insert the new hero which returns back a pointer to be used
Display the new hero
*/
void purchaseMenu(Database<SmashHero>& database) 
{
	cout << "====================Gachapon=====================" << endl;
	int goldCost = 1000;
	if (database.getGold() >= goldCost)
	{
		cout << "Key\tName\tRarity" << endl;
		SmashHero* newHero = database.purchaseNewHero(100);
		cout << *newHero;
		cout << "\nYou now have " << database.getGold() << " gold.\n\n";
	}
	else 
	{
		cout << "You do not have enough gold to use the Gachapon!\n";
		cout << "\nYou currently have " << database.getGold() << " gold.\n\n";
	}
}

/*
Sell Menu
Prompt user for a primary key to be deleted
use Database::displayHero(int primaryKey)
Confirm delete
use Database::sellHero(int primaryKey)
*/
void sellMenu(Database<SmashHero>& database) 
{
	cout << "====================Sell Menu====================" << endl;
	cout << "Please enter the key of a hero you would like to sell: ";
	int primaryKey;
	cin >> primaryKey;
	cout << endl;
	database.displayHero(primaryKey);
	cout << "\nIs this the hero you would like to sell?(Y/N): ";
	char sellChoice;
	cin >> sellChoice;
	if (sellChoice == 'N' || sellChoice == 'n') 
	{
		return;
	}
	database.sellHero(primaryKey);
}

/*
Hero List Menu
Database::displayHeroList()
*/
void heroListMenu(Database<SmashHero>& database) 
{
	database.displayHeroList();
	cout << endl << endl;
}

/*
Team List Menu

Display Team function call
Prompt user for which slot they want to replace
Prompt user for a primary key they own to be put into that slot
Swap Team Member function call
*/
void teamMenu(Database<SmashHero>& database) 
{
	cout << "====================Team Menu====================" << endl;
	database.displayTeam();
	cout << "\nWhich slot would you like to swap?(6 for exit)";
	int slotChoice;
	cin >> slotChoice;
	if (slotChoice >= 6 || slotChoice <= 0) 
	{
		return;
	}
	cout << "\nWhat hero would you like to put in slot " << slotChoice << "?(Enter hero key) ";
	int swapKey;
	cin >> swapKey;
	cout << "\n\nYou swapped in this hero into slot " << slotChoice << "!\n";
	database.displayHero(swapKey);
	cout << endl << endl;
	database.swapTeamMember(slotChoice, swapKey);
}

/*
Options Menu
Extra menu options for project requirements
1. Add new data							= Database::addCustomHero(string attributeLine)
2. Delete data							= Database::sellHero(int primaryKey)
3. Find and display using primary key	= Database::displayHero(int primaryKey)
4. List data in hash table sequence		= Database::displayHeroList()
5. List data in key sequence (sorted)	= Database::displayOrderedList()
6. Print indented tree					= Database::printIndentedTree()
7. Efficiency							= Database::displayEfficiency()
8. Exit (Team Choice is the battle menu)
*/
void optionsMenu(Database<SmashHero>& database) 
{

}