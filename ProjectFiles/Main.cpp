#include <iostream>
#include <string>
#include "BST.h"
#include "HashTable.h"
#include "SmashHero.h"

using namespace std;

/*
void battleMenu();
void purchaseMenu();
void sellMenu();
void heroListMenu();
void partyMenu();
void optionsMenu();
*/

/*
void loadSave(fstream& saveFile, BST& heroTree, HashTable& heroDatabase);
	Load the save file onto saveFile
	Count the # of lines, reset file pointer
	Create HashTable based on the size (maybe a table of # ranges to associated prime numbers)
	(if we do the party list, load first line into party list)
	Create new SmashHeroes for each line and insert into BST and Hashtable

void saveToFile(fstream& saveFile, HashTable& heroDatabase);
	clear saveFile
	(if we do the party list, load party to first line)
	HashTable inSequence function call with prints to file instead of couts?
*/

int main() {

	bool ExitMainMenu = false;

	do {
		cout << "====================Main Menu====================" << endl;
		cout << "1. To Battle!" << endl;
		cout << "2. Purchase New Hero" << endl;
		cout << "3. Sell Hero" << endl;
		cout << "4. Hero List" << endl;
		cout << "5. Party Menu" << endl;
		cout << "6. Options Menu" << endl;
		cout << "7. Exit Game" << endl << endl;

		int userChoice;

		cin >> userChoice;

		switch (userChoice) {
		case 1:
			/*
			5 Hero array with current team
			1 2 3 4 5
			3 gets 3 xp?
			2 & 4 get 2 xp
			1 & 5 get 1 xp
			Return gold value?
			Different missions?
			*/
			break;
		case 2:
			/*
			Subtract from gold value
			Create new SmashHero using a special fstream file constructor (Full Hero List)
				Rarity roll from 1-100, Randomly select a hero with that rarity from file
					i.e. if 99, rarityIndex = 4, RNG from 1-6 select from main file with that line #
			Display the new Hero
			Insert new SmashHero into BST and HashTable
			*/
			break;
		case 3:
			/*
			Prompt user for a primary key to be deleted
			Display to be deleted hero (HashTable search function)
			HashTable delete function call passing the primary key
			*/
			break;
		case 4:
			/*
			HashTable inSequence function call
			*/
			break;
		case 5:
			/*
			5 hero array display function call
			Prompt user for which slot they want to replace
			Prompt user for a primary key they own to be put into that slot
			Replace heroArray[slot] with database->heroList[primaryKey]
			*/
			break;
		case 6:
			//optionsMenu();
			break;
		case 7:
			ExitMainMenu = true;
			break;
		default:
			break;
		}
		
	} while (!ExitMainMenu);


	return 0;
}


//void optionsMenu() {
//cout << "=================Options Menu====================" << endl;
//cout << "1. Add custom data" << endl;
//cout << "2. Search data by primary key" << endl;
//cout << "3. List data in hash table sequence" << endl;
//cout << "4. List data by key" << endl;
//cout << "5. Print indented tree" << endl;
//cout << "6. Display efficiency stats" << endl;
//cout << "7. Exit" << endl << endl;
//
//int optionsMenuChoice;
//cin >> optionsMenuChoice;
//
//switch (optionsMenuChoice) {
//case 1:
///*
//Declare temp attributes as strings
//Prompt user to input each attribute
//Concatenate attributes into 1 line
//Create new SmashHero constructed with the line
//Insert the new SmashHero into the BST and HashTable
//*/
//break;
//	case 2:
//		/*
//		Prompt user for a primary key as double
//		HashTable search function using primary key
//		*/
//		break;
//	case 3:
//		/*
//		HashTable inSequence function call
//		*/
//		break;
//	case 4:
//		/*
//		BST inOrderTraversal function call
//		*/
//		break;
//	case 5:
//		/*
//		BST printIndentedTree function call
//		*/
//		break;
//	case 6:
//		/*
//		HashTable printEfficiency function call
//		*/
//		break;
//	case 7:
//		break;
//	}
//
//}