#ifndef DATABASE_H
#define DATABASE_H

#include "Hashtable.h"
#include "BST.h"
#include "SmashHero.h"

#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <class T>
class Database {
private:
	fstream saveFile; //The file used to load and save data from
	fstream heroList; //List of potential heroes you can get
	HashTable hashTable; //Hashtable of currently owned Heroes
	BST<T> binarySearchTree; //Sorted tree of currently owned Heroes
	//int teamList[5]; //primaryKeys of last used Team
	vector<int> teamList; //vector of primaryKeys of last used Team
	int gold; //Gold value gained through doing battles

	vector<int> enemyteamList; //vector of primaryKeys of randomly generated Enemy Team.

public:
	Database(fstream& saveFile);

	SmashHero* purchaseNewHero(int goldCost);
	void sellHero(int primaryKey);
	void displayHeroList();
	void displayOrderedList();
	void swapTeamMember(int slot, int primaryKey);
	void addCustomHero(string attributeLine);
	void searchByKey(int primaryKey);
	void printIndentedTree();
	void displayEfficiency();
	void saveToFile();
	void insertNewHero(T data);
	void displayTeam();
	void displayHero(int primaryKey);

	///////////////////////////////// Battle System
	bool teamBattle();

	~Database();
};

//Takes in a file and loads in data, creates, and initializes the hash table and BST
template <class T>
Database<T>::Database(fstream& saveFile) {
	/*
	Read how many lines are in the file
	Create hash table using next best prime number
	Load gold and team list (still thinking of how this can be done
	Load rest of file into the hashTable and binarySearchTree
	Loop while not at the end of file
	Get line until new line, store into temp string
	Make temp SmashHero pointer and create a new SmashHero using the constructor that takes an attribute string
	insert temp SmashHero pointer using Database::insertNewHero
	*/

	this->saveFile = saveFile;

}

//Increments the stats? of the heroes in the team and gives some gold value
template <class T>
bool Database<T>::teamBattle()
{
	///////////////// Initialize your party and the enemy's into vectors for ease of use.
	vector <SmashHero*> Members;
	int totalLevels = 0;
	for (int i = 1; i < teamList.size(); i++)
	{
		Members.push_back(hashTable.getItem(teamList[i]));
		totalLevels += Members[i]->getLevel();
	}
	vector <SmashHero*> EnemyMembers;
	for (int i = 1; i < enemyteamList.size(); i++)
	{
		EnemyMembers.push_back(hashTable.getItem(enemyteamList[i]));
		EnemyMembers[i]->AdjustDifficulty(totalLevels);
	}
	int TurnNumber = 1;
	bool battleResult = false;
	bool battlecompleted = false;
	do
	{
		cout << "Turn " << TurnNumber << ": " << endl;
		///////////////// Prints out the members in party and enemy team as well as randomizes everyone's turn order.
		for (int i = 1; i < teamList.size(); i++)
		{
			if (Members[i] != NULL)
			{
				cout << "\t" << Members[i]->getHeroName() << " HP: " << Members[i]->getHeroHP() << "/" << Members[i]->getHeroMaxHP;
				Members[i]->setTurnOrder();
			}
			if (EnemyMembers[i] != NULL)
			{
				cout << "\t" << EnemyMembers[i]->getHeroName() << " HP: " << EnemyMembers[i]->getHeroHP() << "/" << EnemyMembers[i]->getHeroMaxHP;
				EnemyMembers[i]->setTurnOrder();
			}
			cout << endl;
		}
		///////////////// Initiate combat. Go by turn order and randomize target. Check if attack missed. Always check if HP is already 0 or below 0. If so, end turn for that hero or enemy.
		for (int i = 1; i < 11; i++)											// first for loop is for Turn order.
		{
			for (int j = 1; j < teamList.size(); j++)							// second for loop will loop through each hero and enemy to find who has the Turn order i.
			{
				if (Members[j]->getTurnOrder() == i)							// if Member j has Turn Order i, then proceed with combat.
				{
					if (Members[j]->isKnockedOut() == false)							// if Member j is not knocked out, proceed with picking a target.
					{
						bool isAttackSuccessful = false;
						do                                                      // exits the do while loop when we have made a successful attack.
						{
							int attackpower = Members[j]->getAttackPower();		// get its attack power
							int k = rand() % enemyteamList.size() - 1;			// randomize its target.
							if (EnemyMembers[k]->isKnockedOut() == false)				// checks if the target is already knocked out. If not, then search for another target.
							{
								if (Members[j]->didWeHit() == false)						// Hit chance mechanic
								{
									cout << "Your " << Members[j]->getHeroName() << " missed its attack!" << endl;
									isAttackSuccesful = true;					// Target dodged the attack so end turn for Member j.
								}
								else
								{
									int defensepower = EnemyMembers[k]->getDefensePower();
									attackpower = attackpower - defensepower;
									///////////////////////////////////// Graze damage mechanic in case attackpower became 0 or negative after subtracting defensepower from it.
									if (attackpower <= 0)						
									{
										if (Members[j]->getLevel() <= 15)
										{
											attackpower = rand() % 5 - 3;
										}
										else if (Members[j]->getLevel() > 15 && Members[j]->getLevel() <= 50)
										{
											attackpower = rand() % 8 - 6;
										}
										else if (Members[j]->getLevel() > 50 && Members[j]->getLevel() <= 100)
										{
											attackpower = rand() % 13 - 8;
										}
										else if (Members[j]->getLevel() > 100 && Members[j]->getLevel() <= 300)
										{
											attackpower = rand() % 18 - 15;
										}
										else if (Members[j]->getLevel() > 300 && Members[j]->getLevel() <= 600)
										{
											attackpower = rand() % 25 - 18;
										}
										else
										{
											attackpower = rand() % 35 - 28;
										}
									}
									EnemyMembers[k]->LoseHP(attackpower);		// and then attack that target.
									cout << "Your " << Members[j]->getHeroName() << " attacked the enemy's " << EnemyMembers[k]->getHeroName() << " for " << attackpower;
									////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
									if (EnemyMembers[k]->isKnockedOut() == false) { cout << " Their " << EnemyMembers[k]->getHeroName() << " is now at HP: " << EnemyMembers[k]->getHeroHP() << "/" << EnemyMembers[k]->getHeroMaxHP() << endl; }
									else if (EnemyMembers[k]->isKnockedOut() == true) { cout << " Their " << EnemyMembers[k]->getHeroName() << " has been knocked out!" << endl; }
									isAttackSuccessful = true;
								}
							}
						} while (!isAttackSuccessful);
					}
				}
				else if (EnemyMembers[j]->getTurnOrder() == i)					// if EnemyMember j has Turn Order i, then proceed with combat.
				{
					if (EnemyMembers[j]->isKnockedOut() == false)						// if EnemyMember j is not knocked out, proceed with picking a target.
					{
						bool isAttackSuccessful = false;
						do                                                      // exits the do while loop when the enemy have made a successful attack.
						{
							int attackpower = EnemyMembers[j]->getAttackPower();// get its attack power
							int k = rand() % teamList.size() - 1;				// randomize its target.
							if (!Members[k]->isKnockedOut())					// checks if the target is already knocked out. If not, then search for another target.
							{
								if (!EnemyMembers[j]->didTheyHit())					// Hit chance mechanic
								{
									cout << "Your " << EnemyMembers[j]->getHeroName() << " missed its attack!" << endl;
									isAttackSuccesful = true;					// Target dodged the attack so end turn for EnemyMember j.
								}
								else
								{
									Members[k]->LoseHP(attackpower);			// and then attack that target.
									cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " attacked your " << Members[k]->getHeroName() << " for " << attackpower;
									////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
									if (Members[k]->isKnockedOut() == false) { cout << " Our " << Members[k]->getHeroName() << " is now at HP: " << Members[k]->getHeroHP() << "/" << Members[k]->getHeroMaxHP() << endl; }
									else if (Members[k]->isKnockedOut() == true) { cout << " Our " << Members[k]->getHeroName() << " has been knocked out!" << endl; }
									isAttackSuccessful = true;
								}
							}
						} while (!isAttackSuccessful);
					}
				}
			}
		}
		////////////////// now check which team won by counting knocked out members.
		int knockedout = 0;
		int enemyknockedout = 0;
		for (int i = 1; i < teamList.size(); i++)
		{
			if (Members[i]->isKnockedOut() == true)
			{
				knockedout++;
			}
			else if (EnemyMembers[i]->isKnockedOut() == true)
			{
				enemyknockedout++;
			}
		}
		if (knockedout == teamList.size())
		{
			cout << endl << "Your team has been wiped out! You have lost this battle!" << endl;
			battlecompleted = true;	// exit out the loop since we lost.
			battleResult = false;	// false for we lost.
		}
		else if (enemyknockedout == enemyteamList.size())
		{
			cout << endl << "The enemy team has been wiped out! You have won this battle!" << endl;
			battlecompleted = true;	// exit out the loop since we won.
			battleResult = true;	// true for we won.
		}
		else
		{
			cout << endl << "Turn " << TurnNumber << " has been completed." << endl;
			TurnNumber++;			// After Turn is completed, move to the next turn until either team is wiped out.
		}
		system("PAUSE");			// This allows the user to read what happened.
		system("cls");
	} while (!battlecompleted);
	////////////////////////// distribute gold and/or exp and call LevelUp if won to improve Attack and Defense stat.

	if (battleResult == true)		// if we won, reward us.
	{
		cout << "===================Victory!==================\n";
		int chance = rand() % 100 - 1; // rolling for increased gold and EXP reward.
									   // considering reducing the reward based on number of knocked out party members...
		if (chance <= 20)
		{
			gold += 250;
			cout << "You have earned a pittance of 250 gold for a total of " << gold << endl;
			for (int i = 0; i < teamList.size(); i++)
			{
				if (Members[i]->isKnockedOut)	// if this party member is knocked out, they gain only half EXP.
				{
					Members[i]->setEXP(15);
				}
				else
				{
					Members[i]->setEXP(30);
				}
			}
		}
		else if (chance > 20 && chance < 90)
		{
			gold += 500;
			cout << "You have earned a reward of 500 gold for a total of " << gold << endl;
			for (int i = 0; i < teamList.size(); i++)
			{
				if (Members[i]->isKnockedOut)	// if this party member is knocked out, they gain only half EXP.
				{
					Members[i]->setEXP(25);
				}
				else
				{
					Members[i]->setEXP(50);
				}
			}
		}
		else if (chance >= 90)
		{
			gold += 750;
			cout << "Congratulations! Lady Luck favors you and gifts you 750 gold for a grand total of " << gold << endl;
			for (int i = 0; i < teamList.size(); i++)
			{
				if (Members[i]->isKnockedOut)	// if this party member is knocked out, they gain only half EXP.
				{
					Members[i]->setEXP(35);
				}
				else
				{
					Members[i]->setEXP(75);
				}
			}
		}
	}
	else
	{
		cout << "===================You Lost!==================\n";
		int chance = rand() % 100 - 1; // rolling for increased gold and EXP reward.
									   // considering reducing the reward based on number of knocked out party members...
		if (chance <= 25)
		{
			gold += 50;
			cout << "You managed to scrounge together a measly 50 gold for a total of " << gold << endl;
			for (int i = 0; i < teamList.size(); i++)
			{
				if (Members[i]->isKnockedOut)	// if this party member is knocked out, they gain only half EXP.
				{
					Members[i]->setEXP(5);
				}
				else
				{
					Members[i]->setEXP(10);
				}
			}
		}
		else
		{
			cout << "You were taken pity upon by a traveling stranger and was gifted 100 gold for a total of " << gold << endl;
			for (int i = 0; i < teamList.size(); i++)
			{
				if (Members[i]->isKnockedOut)	// if this party member is knocked out, they gain only half EXP.
				{
					Members[i]->setEXP(10);
				}
				else
				{
					Members[i]->setEXP(20);
				}
			}
		}
	}
}

//Purchases a new hero by RNG
template <class T>
SmashHero* Database<T>::purchaseNewHero(int goldCost) {
	/*
	Subtract gold value
	Create a random number between 1-100 for rarity %'s
	Depending on rarity index, Get a random number with associated lines in the Hero List file
	Go to line in file and read into a string
	Create new SmashHero object at a pointer passing in the attribute string for the constructor
	Call insertNewHero function
	*/
	//Removing gold cost
	this->gold -= goldCost;

	//Generating a random number to pull from the hero list
	srand(time(NULL));
	int rngesus = rand() % 100 + 1;
	if (rngesus > 98) {
		rngesus = rand() % 6;
	}
	else if (rngesus > 85) {
		rngesus = rand() % 3 + 6;
	}
	else if (rngesus > 60) {
		rngesus = rand() % 24 + 9;
	}
	else {
		rngesus = rand() % 24 + 33;
	}

	//Finding the hero in the hero list and creating it
	string line;
	this->heroList.seekg(this->heroList.beg);
	for (int i = 0; i > rngesus; i++) {
		getline(this->heroList, line);
	}
	this->heroList.seekg(this->heroList.beg);
	SmashHero* tempPtr = new SmashHero(line);

	//Insert new hero into the Hash Table and BST

	//Returning the tempPtr to be used in main
	return tempPtr;
}

//Removes a hero from the database by primaryKey
template <class T>
void Database<T>::sellHero(int primaryKey) {
	/*
	Make temp pointer to SmashHero searched through Hash Table using primary key
	Call hashTable delete function
	Call BST delete function
	(If theres gold values associated with heroes, increase gold)
	Delete temp
	*/
	SmashHero* tempPtr = hashTable.getItem(primaryKey);
	if (tempPtr != nullptr) {
		//Add Gold?
		//Call hashTable and BST delete functions
		//hashTable.deleteItem(tempPtr);
		delete tempPtr;
	}
}

//Displays the hero list in the hash table sequence
template <class T>
void Database<T>::displayHeroList() {
	/*
	call HashTable display function
	*/
}

//Displays the hero list in order using the BST
template <class T>
void Database<T>::displayOrderedList() {
	/*
	call BST display inOrder function
	*/
}

//Switches the team list slot to the new primaryKey
template <class T>
void Database<T>::swapTeamMember(int slot, int primaryKey) {
	this->teamList[slot - 1] = primaryKey;
}

//Makes a new hero using the given attribute line, adding it to the hash table and BST
template <class T>
void Database<T>::addCustomHero(string attributeLine) {
	SmashHero* tempPtr = new SmashHero(attributeLine);
	//Call the HashTable and BST insert functions
}

//Searches the Hash Table for the primary key and displays the hero if found
template <class T>
void Database<T>::searchByKey(int primaryKey) {
	/*
	Call Hash Table search function and display the hero with that key
	*/
}

//Prints out the tree indented by height
template <class T>
void Database<T>::printIndentedTree() {
	/*
	Calls the BST print indented tree function
	*/
}

//Displays the efficiency statistics of the Hash Table
template <class T>
void Database<T>::displayEfficiency() {
	/*
	Calls the Hash Table display efficiency function
	*/
}

//Saves the current data set to the file
template <class T>
void Database<T>::saveToFile() {
	/*
	Clear old save file
	Save the current team and current gold onto the first 2 lines
	Read the Hash Table in sequence onto the file
	*/
}

template <class T>
void Database<T>::insertNewHero(T data) {
	/*
	Calls the HashTable and BST insert functions passing in the SmashHero pointer
	*/
}

//Displays the current team (Still needs some special graphic or something)
template <class T>
void Database<T>::displayTeam() {
	for (int i = 0; i > 5; i++) {
		SmashHero* tempPtr = this->hashTable.getItem(this->teamList[i]);
		if (tempPtr != nullptr) {
			cout << *tempPtr;
		}
	}
}

//Displays a hero with the given
template <class T>
void Database<T>::displayHero(int primaryKey) {
	SmashHero* tempPtr = this->hashTable.getItem(primaryKey);
	if (tempPtr != nullptr) {
		cout << *tempPtr;
	}
}

#endif DATABASE_H
