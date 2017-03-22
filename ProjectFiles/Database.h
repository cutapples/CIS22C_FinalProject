#ifndef DATABASE_H
#define DATABASE_H

#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "HashTable.h"
#include "BST.h"
#include "SmashHero.h"

using namespace std;

template <class T>
class Database 
{
private:
	fstream saveFile; //The file used to load and save data from
	fstream heroList; //List of potential heroes you can get
	HashTable hashTable; //Hashtable of currently owned Heroes
	BST<T> binarySearchTree; //Sorted tree of currently owned Heroes
	vector<int> teamList; //primaryKeys of last used Team
	int gold; //Gold value gained through doing battles

public:
	Database();

	SmashHero* purchaseNewHero(int goldCost);
	void sellHero(int primaryKey);
	void displayHeroList();
	void displayTeam();

	void addCustomHero(string attributeLine);
	void displayHero(int primaryKey);
	void displayOrderedList();
	void printIndentedTree();
	void displayEfficiency();

	void swapTeamMember(int slot, int primaryKey);
	void saveToFile();
	void insertNewHero(SmashHero* data);
	SmashHero* getHero(int primaryKey);
	int getGold() { return this->gold; };

	void teamBattle();
	void healUs();
	void GenerateRandomStatsTeam();
	void GenerateRandomEnemyTeam(vector<SmashHero*>& EnemyMembers);
	
	~Database();
};

//Takes in a file and loads in data, creates, and initializes the hash table and BST
template <class T>
Database<T>::Database() 
{
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
	saveFile.open("SaveFile.txt");
	if (saveFile.fail()) 
	{
		cout << "Error: Save file not found.\nCreating empty save file.\n";
		saveFile.close();
		saveFile.open("SaveFile.txt", ios::out);
		saveFile.close();
		saveFile.open("SaveFile.txt");
		cout << "Empty save file created.\n";
	}
	heroList.open("HeroList.txt");
	if (heroList.fail()) 
	{
		cout << "Error: Hero file not found.\nCreating empty hero file.\n";
		heroList.close();
		heroList.open("HeroList.txt", ios::out);
		heroList.close();
		heroList.open("HeroList.txt");
		cout << "Empty hero list file created.\n";
	}

	saveFile.seekg(saveFile.beg);

	string gold = "0";
	string tempTeam = "0\t0\t0\t0\t0";
	string line;
	if (!saveFile.eof()) 
	{
		getline(saveFile, gold);
	}

	this->gold = stoi(gold);

	if (!saveFile.eof()) 
	{
		getline(saveFile, tempTeam);
	}

	int space1 = tempTeam.find('\t');
	int space2 = tempTeam.find('\t', space1 + 1);
	int space3 = tempTeam.find('\t', space2 + 1);
	int space4 = tempTeam.find('\t', space3 + 1);

	teamList.push_back(stoi(tempTeam.substr(0, space1)));
	teamList.push_back(stoi(tempTeam.substr(space1 + 1, space2 - space1 - 1)));
	teamList.push_back(stoi(tempTeam.substr(space2 + 1, space3 - space2 - 1)));
	teamList.push_back(stoi(tempTeam.substr(space3 + 1, space4 - space3 - 1)));
	teamList.push_back(stoi(tempTeam.substr(space4 + 1, tempTeam.length() - space4)));

	while (!saveFile.eof()) 
	{
		SmashHero* ptr;
		getline(saveFile, line);
		if (line != "")
		{
			ptr = new SmashHero(line);
			insertNewHero(ptr);
		}
	}

	saveFile.seekg(saveFile.beg);
	heroList.seekg(heroList.beg);

	//Initializing Team
	for (int i = 0; i < teamList.size(); i++)
	{
		SmashHero* tempPtr = hashTable.getItem(teamList[i]);
		tempPtr->GenerateStats();
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
	int rngesus = (rand() * 37) % 100 + 1;
	if (rngesus > 98) 
	{
		rngesus = (rand() * 71) % 6;
	}
	else if (rngesus > 85) 
	{
		rngesus = (rand() * 197) % 3 + 6;
	}
	else if (rngesus > 60) 
	{
		rngesus = (rand() * 613) % 24 + 9;
	}
	else 
	{
		rngesus = (rand() * 269) % 24 + 33;
	}

	//Finding the hero in the hero list and creating it
	string line;
	this->heroList.seekg(this->heroList.beg);
	for (int i = 0; i < rngesus; i++) 
	{
		getline(this->heroList, line);
	}
	this->heroList.seekg(this->heroList.beg);
	if (line != "")
	{
		SmashHero* tempPtr = new SmashHero(line);

		//Insert new hero into the Hash Table and BST
		insertNewHero(tempPtr);

		//Returning the tempPtr to be used in main
		return tempPtr;
	}
	else 
	{
		SmashHero* tempPtr = nullptr;
		return tempPtr;
	}
}

//Removes a hero from the database by primaryKey
template <class T>
void Database<T>::sellHero(int primaryKey) 
{
	/*
	Make temp pointer to SmashHero searched through Hash Table using primary key
	Call hashTable delete function
	Call BST delete function
	(If theres gold values associated with heroes, increase gold)
	Delete temp
	*/

	SmashHero* tempPtr = hashTable.getItem(primaryKey);
	if (tempPtr != nullptr) 
	{
		this->gold += (5 - tempPtr->getRarityIndex()) * 10;
		binarySearchTree.remove(*tempPtr);
		hashTable.removeItem(tempPtr->getPrimaryKey());
		delete tempPtr;
	}
}

//Displays the hero list in the hash table sequence
template <class T>
void Database<T>::displayHeroList() 
{
	cout << hashTable;
}

//Displays the current team (Still needs some special graphic or something)
template <class T>
void Database<T>::displayTeam() 
{
	for (int i = 0; i < teamList.size(); i++) 
	{
		SmashHero* tempPtr = this->hashTable.getItem(this->teamList[i]);
		if (tempPtr != nullptr) 
		{
			cout << *tempPtr << endl;
		}
	}
}

//Makes a new hero using the given attribute line, adding it to the hash table and BST
template <class T>
void Database<T>::addCustomHero(string attributeLine) 
{
	SmashHero* tempPtr = new SmashHero(attributeLine);
	insertNewHero(tempPtr);
}

//Displays a hero with the given
template <class T>
void Database<T>::displayHero(int primaryKey) 
{
	SmashHero* tempPtr = this->hashTable.getItem(primaryKey);
	if (tempPtr != nullptr) 
	{
		cout << *tempPtr;
	}
}

//Displays the hero list in order using the BST
template <class T>
void Database<T>::displayOrderedList() 
{
	binarySearchTree.print_inOrder();
}

//Prints out the tree indented by height
template <class T>
void Database<T>::printIndentedTree() 
{
	binarySearchTree.print_preOrder();
}

//Displays the efficiency statistics of the Hash Table
template <class T>
void Database<T>::displayEfficiency() 
{
	hashTable.displayEfficiency();
}

//Switches the team list slot to the new primaryKey
template <class T>
void Database<T>::swapTeamMember(int slot, int primaryKey) 
{
	this->teamList[slot - 1] = primaryKey;
}

//Saves the current data set to the file
template <class T>
void Database<T>::saveToFile() 
{
	/*
	Clear old save file
	Save the current team and current gold onto the first 2 lines
	Read the Hash Table in sequence onto the file
	*/
	saveFile.clear();

	//Erasing old save file
	saveFile.close();
	remove("SaveFile.txt");
	saveFile.open("SaveFile.txt");
	if (saveFile.fail())
	{
		saveFile.close();
		saveFile.open("SaveFile.txt", fstream::out);
		saveFile.close();
		saveFile.open("SaveFile.txt");
	}

	saveFile << gold << endl;
	for (int i = 0; i < teamList.size() - 1; i++) 
	{
		saveFile << teamList[i] << "\t";
	}
	saveFile << teamList[teamList.size() - 1] << endl;
	saveFile << hashTable;
}

//Inserts a new hero into the HashTable and the BST
template <class T>
void Database<T>::insertNewHero(SmashHero* data) 
{
	binarySearchTree.insert(*data);
	hashTable.addItem(data);
}

//Returns a pointer to the hero that is searched for
template <class T>
SmashHero* Database<T>::getHero(int primaryKey) 
{
	SmashHero* tempPtr = this->hashTable.getItem(primaryKey);
	return tempPtr;
}

template <class T>
void Database<T>::teamBattle() 
{
	/////////////////////////////////////////// Initialize your party and the enemy's party into vectors for ease of use.
	vector <SmashHero*> Members;
	int totalLevels = 0;
	for (int i = 0; i < teamList.size(); i++) 
	{
		Members.push_back(hashTable.getItem(teamList[i]));
		totalLevels += Members[i]->getLevel();
	}

	vector <SmashHero*> EnemyMembers;
	GenerateRandomEnemyTeam(EnemyMembers);				// fill up the vector of enemyteamList with random heroes

	for (int i = 0; i < EnemyMembers.size(); i++) 
	{
		EnemyMembers[i]->AdjustDifficulty(totalLevels);	//auto generate their stats.
	}
	int TurnNumber = 1;
	bool battleResult = false;
	bool battlecompleted = false;
	bool isAttackSuccessful = false;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	do 
	{
		cout << "Turn " << TurnNumber << ": " << endl;
		////////////////////////////////////// Prints out the members in party and enemy team.
		cout << "\tYour Team" << "\tEnemy Team" << endl;
		for (int i = 0; i < teamList.size(); i++) 
		{
			if (Members[i] != NULL) 
			{	
				cout << "\t" << Members[i]->getHeroName() << " HP: " << Members[i]->getHeroHP() << "/" << Members[i]->getHeroMaxHP();
			}
			if (EnemyMembers[i] != NULL) 
			{
				cout << "\t" << EnemyMembers[i]->getHeroName() << " HP: " << EnemyMembers[i]->getHeroHP() << "/" << EnemyMembers[i]->getHeroMaxHP();
			}
			cout << endl;
		}
		////////////////////////////////////// Sets Turn Order.
		Members[0]->setTurnOrder(1);
		EnemyMembers[0]->setTurnOrder(2);
		Members[1]->setTurnOrder(3);
		EnemyMembers[1]->setTurnOrder(4);
		Members[2]->setTurnOrder(5);
		EnemyMembers[2]->setTurnOrder(6);
		Members[3]->setTurnOrder(7);
		EnemyMembers[3]->setTurnOrder(8);
		Members[4]->setTurnOrder(9);
		EnemyMembers[4]->setTurnOrder(10);
		cout << endl;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////// Initiate combat. Go by turn order and randomize target. Check if attack missed. Always check if HP is already 0 or below 0. If so, end turn for that hero or enemy.
		int ourTeamKnockedOut = 0;
		int theirTeamKnockedOut = 0;
		for (int i = 1; i < 11; i++)										// first for loop is for Turn order.
		{
			for (int j = 0; j < teamList.size(); j++)						// second for loop will loop through each hero and enemy to find who has the Turn order i.
			{
				ourTeamKnockedOut = 0;
				theirTeamKnockedOut = 0;
				for (int i = 0; i < teamList.size(); i++)
				{
					if (Members[i]->isKnockedOut())
					{
						ourTeamKnockedOut++;
					}
					if (EnemyMembers[i]->isKnockedOut())
					{
						theirTeamKnockedOut++;
					}
				}
				if (ourTeamKnockedOut != teamList.size() && theirTeamKnockedOut != teamList.size())
				{
					if (Members[j]->getTurnOrder() == i)						// if Member j has Turn Order i, then proceed with combat.
					{
						if (Members[j]->isKnockedOut() == false)				// if Member j is not knocked out, proceed with picking a target.
						{
							bool isAttackSuccessful = false;
							ourTeamKnockedOut = 0;
							theirTeamKnockedOut = 0;
							for (int i = 0; i < teamList.size(); i++)
							{
								if (Members[i]->isKnockedOut())
								{
									ourTeamKnockedOut++;
								}
								if (EnemyMembers[i]->isKnockedOut())
								{
									theirTeamKnockedOut++;
								}
							}
							if (ourTeamKnockedOut != teamList.size())
							{
								do                                                  // exits the do while loop when we have made a successful attack.
								{
									int k = 0;
									if (EnemyMembers[0]->isKnockedOut() == false)
									{
										k = 0;
										int attackpower = Members[j]->getAttackPower();
										int defensepower = EnemyMembers[k]->getDefensePower();
										attackpower = attackpower - defensepower;

										///////////////////////////////////// Graze damage mechanic in case attackpower became 0 or negative after subtracting defensepower from it.
										if (attackpower <= 0)
										{
											// These values are taken straight from the AdjustDifficulty() from SmashHero.h
											if (Members[j]->getLevel() <= 15) { attackpower = 5; }
											else if (Members[j]->getLevel() > 15 && Members[j]->getLevel() <= 50) {attackpower = 10; }
											else if (Members[j]->getLevel() > 50 && Members[j]->getLevel() <= 100){ attackpower = 15; }
											else if (Members[j]->getLevel() > 100 && Members[j]->getLevel() <= 300){ attackpower = 20; }
											else if (Members[j]->getLevel() > 300 && Members[j]->getLevel() <= 600){ attackpower = 25; }
											else{ attackpower = 30; }
										}
										
										EnemyMembers[k]->LoseHP(attackpower);	// and then attack that target.
										cout << "Your " << Members[j]->getHeroName() << " attacked the enemy's " << EnemyMembers[k]->getHeroName() << " for " << attackpower << endl;
										////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
										if (EnemyMembers[k]->isKnockedOut() == false) { cout << "Their " << EnemyMembers[k]->getHeroName() << " is now at HP: " << EnemyMembers[k]->getHeroHP() << "/" << EnemyMembers[k]->getHeroMaxHP() << endl << endl; }
										else if (EnemyMembers[k]->isKnockedOut() == true) { cout << "Their " << EnemyMembers[k]->getHeroName() << " has been knocked out!" << endl << endl; }
										isAttackSuccessful = true;
									}
									else if (EnemyMembers[1]->isKnockedOut() == false)
									{
										k = 1;
										int attackpower = Members[j]->getAttackPower();
										int defensepower = EnemyMembers[k]->getDefensePower();
										attackpower = attackpower - defensepower;
										
										///////////////////////////////////// Graze damage mechanic in case attackpower became 0 or negative after subtracting defensepower from it.
										if (attackpower <= 0)
										{
											// These values are taken straight from the AdjustDifficulty() from SmashHero.h
											if (Members[j]->getLevel() <= 15) { attackpower = 5; }
											else if (Members[j]->getLevel() > 15 && Members[j]->getLevel() <= 50) { attackpower = 10; }
											else if (Members[j]->getLevel() > 50 && Members[j]->getLevel() <= 100) { attackpower = 15; }
											else if (Members[j]->getLevel() > 100 && Members[j]->getLevel() <= 300) { attackpower = 20; }
											else if (Members[j]->getLevel() > 300 && Members[j]->getLevel() <= 600) { attackpower = 25; }
											else { attackpower = 30; }
										}
										
										EnemyMembers[k]->LoseHP(attackpower);	// and then attack that target.
										cout << "Your " << Members[j]->getHeroName() << " attacked the enemy's " << EnemyMembers[k]->getHeroName() << " for " << attackpower << endl;
										////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
										if (EnemyMembers[k]->isKnockedOut() == false) { cout << "Their " << EnemyMembers[k]->getHeroName() << " is now at HP: " << EnemyMembers[k]->getHeroHP() << "/" << EnemyMembers[k]->getHeroMaxHP() << endl << endl; }
										else if (EnemyMembers[k]->isKnockedOut() == true) { cout << "Their " << EnemyMembers[k]->getHeroName() << " has been knocked out!" << endl << endl; }
										isAttackSuccessful = true;
									}
									else if (EnemyMembers[2]->isKnockedOut() == false)
									{
										k = 2;
										int attackpower = Members[j]->getAttackPower();
										int defensepower = EnemyMembers[k]->getDefensePower();
										attackpower = attackpower - defensepower;
										
										///////////////////////////////////// Graze damage mechanic in case attackpower became 0 or negative after subtracting defensepower from it.
										if (attackpower <= 0)
										{
											// These values are taken straight from the AdjustDifficulty() from SmashHero.h
											if (Members[j]->getLevel() <= 15) { attackpower = 5; }
											else if (Members[j]->getLevel() > 15 && Members[j]->getLevel() <= 50) { attackpower = 10; }
											else if (Members[j]->getLevel() > 50 && Members[j]->getLevel() <= 100) { attackpower = 15; }
											else if (Members[j]->getLevel() > 100 && Members[j]->getLevel() <= 300) { attackpower = 20; }
											else if (Members[j]->getLevel() > 300 && Members[j]->getLevel() <= 600) { attackpower = 25; }
											else { attackpower = 30; }
										}
										
										EnemyMembers[k]->LoseHP(attackpower);	// and then attack that target.
										cout << "Your " << Members[j]->getHeroName() << " attacked the enemy's " << EnemyMembers[k]->getHeroName() << " for " << attackpower << endl;
										////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
										if (EnemyMembers[k]->isKnockedOut() == false) { cout << "Their " << EnemyMembers[k]->getHeroName() << " is now at HP: " << EnemyMembers[k]->getHeroHP() << "/" << EnemyMembers[k]->getHeroMaxHP() << endl << endl; }
										else if (EnemyMembers[k]->isKnockedOut() == true) { cout << "Their " << EnemyMembers[k]->getHeroName() << " has been knocked out!" << endl << endl; }
										isAttackSuccessful = true;
									}
									else if (EnemyMembers[3]->isKnockedOut() == false)
									{
										k = 3;
										int attackpower = Members[j]->getAttackPower();
										int defensepower = EnemyMembers[k]->getDefensePower();
										attackpower = attackpower - defensepower;
										
										///////////////////////////////////// Graze damage mechanic in case attackpower became 0 or negative after subtracting defensepower from it.
										if (attackpower <= 0)
										{
											// These values are taken straight from the AdjustDifficulty() from SmashHero.h
											if (Members[j]->getLevel() <= 15) { attackpower = 5; }
											else if (Members[j]->getLevel() > 15 && Members[j]->getLevel() <= 50) { attackpower = 10; }
											else if (Members[j]->getLevel() > 50 && Members[j]->getLevel() <= 100) { attackpower = 15; }
											else if (Members[j]->getLevel() > 100 && Members[j]->getLevel() <= 300) { attackpower = 20; }
											else if (Members[j]->getLevel() > 300 && Members[j]->getLevel() <= 600) { attackpower = 25; }
											else { attackpower = 30; }
										}
										
										EnemyMembers[k]->LoseHP(attackpower);	// and then attack that target.
										cout << "Your " << Members[j]->getHeroName() << " attacked the enemy's " << EnemyMembers[k]->getHeroName() << " for " << attackpower << endl;
										////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
										if (EnemyMembers[k]->isKnockedOut() == false) { cout << "Their " << EnemyMembers[k]->getHeroName() << " is now at HP: " << EnemyMembers[k]->getHeroHP() << "/" << EnemyMembers[k]->getHeroMaxHP() << endl << endl; }
										else if (EnemyMembers[k]->isKnockedOut() == true) { cout << "Their " << EnemyMembers[k]->getHeroName() << " has been knocked out!" << endl << endl; }
										isAttackSuccessful = true;
									}
									else if (EnemyMembers[4]->isKnockedOut() == false)
									{
										k = 4;
										int attackpower = Members[j]->getAttackPower();
										int defensepower = EnemyMembers[k]->getDefensePower();
										attackpower = attackpower - defensepower;
										
										///////////////////////////////////// Graze damage mechanic in case attackpower became 0 or negative after subtracting defensepower from it.
										if (attackpower <= 0)
										{
											// These values are taken straight from the AdjustDifficulty() from SmashHero.h
											if (Members[j]->getLevel() <= 15) { attackpower = 5; }
											else if (Members[j]->getLevel() > 15 && Members[j]->getLevel() <= 50) { attackpower = 10; }
											else if (Members[j]->getLevel() > 50 && Members[j]->getLevel() <= 100) { attackpower = 15; }
											else if (Members[j]->getLevel() > 100 && Members[j]->getLevel() <= 300) { attackpower = 20; }
											else if (Members[j]->getLevel() > 300 && Members[j]->getLevel() <= 600) { attackpower = 25; }
											else { attackpower = 30; }
										}
										
										EnemyMembers[k]->LoseHP(attackpower);	// and then attack that target.
										cout << "Your " << Members[j]->getHeroName() << " attacked the enemy's " << EnemyMembers[k]->getHeroName() << " for " << attackpower << endl;
										////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
										if (EnemyMembers[k]->isKnockedOut() == false) { cout << "Their " << EnemyMembers[k]->getHeroName() << " is now at HP: " << EnemyMembers[k]->getHeroHP() << "/" << EnemyMembers[k]->getHeroMaxHP() << endl << endl; }
										else if (EnemyMembers[k]->isKnockedOut() == true) { cout << "Their " << EnemyMembers[k]->getHeroName() << " has been knocked out!" << endl << endl; }
										isAttackSuccessful = true;
									}
									//
									isAttackSuccessful = true;
								} while (isAttackSuccessful != true);
							}
						}
					}
					else if (EnemyMembers[j]->getTurnOrder() == i)				// if EnemyMember j has Turn Order i, then proceed with combat.
					{
						if (EnemyMembers[j]->isKnockedOut() == false)			// if EnemyMember j is not knocked out, proceed with picking a target.
						{
							bool isAttackSuccessful = false;
							do                                                  // exits the do while loop when the enemy have made a successful attack.
							{
								int k = rand() % (teamList.size() - 1) - 1;
								if (k < 0)
								{
									k = 0;
								}
								int attackpower = EnemyMembers[j]->getAttackPower();// get its attack power
								if (Members[0]->isKnockedOut() == false)
								{
									k = 0;
									if (!EnemyMembers[j]->didTheyHit())			// Hit chance mechanic
									{
										cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " missed its attack!" << endl << endl;
										isAttackSuccessful = true;				// Target dodged the attack so end turn for EnemyMember j.
									}
									else
									{
										Members[k]->LoseHP(attackpower);		// and then attack that target.
										cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " attacked your " << Members[k]->getHeroName() << " for " << attackpower << endl;
										////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
										if (Members[k]->isKnockedOut() == false) { cout << "Our " << Members[k]->getHeroName() << " is now at HP: " << Members[k]->getHeroHP() << "/" << Members[k]->getHeroMaxHP() << endl << endl; }
										else if (Members[k]->isKnockedOut() == true) { cout << "Our " << Members[k]->getHeroName() << " has been knocked out!" << endl << endl; }
										isAttackSuccessful = true;
									}
								}
								else if (Members[1]->isKnockedOut() == false)
								{
									k = 1;
									if (!EnemyMembers[j]->didTheyHit())			// Hit chance mechanic
									{
										cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " missed its attack!" << endl << endl;
										isAttackSuccessful = true;				// Target dodged the attack so end turn for EnemyMember j.
									}
									else
									{
										Members[k]->LoseHP(attackpower);		// and then attack that target.
										cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " attacked your " << Members[k]->getHeroName() << " for " << attackpower << endl;
										////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
										if (Members[k]->isKnockedOut() == false) { cout << "Our " << Members[k]->getHeroName() << " is now at HP: " << Members[k]->getHeroHP() << "/" << Members[k]->getHeroMaxHP() << endl << endl; }
										else if (Members[k]->isKnockedOut() == true) { cout << "Our " << Members[k]->getHeroName() << " has been knocked out!" << endl << endl; }
										isAttackSuccessful = true;
									}
								}
								else if (Members[2]->isKnockedOut() == false)
								{
									k = 2;
									if (!EnemyMembers[j]->didTheyHit())			// Hit chance mechanic
									{
										cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " missed its attack!" << endl << endl;
										isAttackSuccessful = true;				// Target dodged the attack so end turn for EnemyMember j.
									}
									else
									{
										Members[k]->LoseHP(attackpower);		// and then attack that target.
										cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " attacked your " << Members[k]->getHeroName() << " for " << attackpower << endl;
										////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
										if (Members[k]->isKnockedOut() == false) { cout << "Our " << Members[k]->getHeroName() << " is now at HP: " << Members[k]->getHeroHP() << "/" << Members[k]->getHeroMaxHP() << endl << endl; }
										else if (Members[k]->isKnockedOut() == true) { cout << "Our " << Members[k]->getHeroName() << " has been knocked out!" << endl << endl; }
										isAttackSuccessful = true;
									}
								}
								else if (Members[3]->isKnockedOut() == false)
								{
									k = 3;
									if (!EnemyMembers[j]->didTheyHit())			// Hit chance mechanic
									{
										cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " missed its attack!" << endl << endl;
										isAttackSuccessful = true;				// Target dodged the attack so end turn for EnemyMember j.
									}
									else
									{
										Members[k]->LoseHP(attackpower);		// and then attack that target.
										cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " attacked your " << Members[k]->getHeroName() << " for " << attackpower << endl;
										////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
										if (Members[k]->isKnockedOut() == false) { cout << "Our " << Members[k]->getHeroName() << " is now at HP: " << Members[k]->getHeroHP() << "/" << Members[k]->getHeroMaxHP() << endl << endl; }
										else if (Members[k]->isKnockedOut() == true) { cout << "Our " << Members[k]->getHeroName() << " has been knocked out!" << endl << endl; }
										isAttackSuccessful = true;
									}
								}
								else if (Members[4]->isKnockedOut() == false)
								{
									k = 4;
									if (!EnemyMembers[j]->didTheyHit())			// Hit chance mechanic
									{
										cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " missed its attack!" << endl << endl;
										isAttackSuccessful = true;				// Target dodged the attack so end turn for EnemyMember j.
									}
									else
									{
										Members[k]->LoseHP(attackpower);		// and then attack that target.
										cout << "The enemy's " << EnemyMembers[j]->getHeroName() << " attacked your " << Members[k]->getHeroName() << " for " << attackpower << endl;
										////////////////////////////////////// print out the resultant HP of the target or if its knocked out.
										if (Members[k]->isKnockedOut() == false) { cout << "Our " << Members[k]->getHeroName() << " is now at HP: " << Members[k]->getHeroHP() << "/" << Members[k]->getHeroMaxHP() << endl << endl; }
										else if (Members[k]->isKnockedOut() == true) { cout << "Our " << Members[k]->getHeroName() << " has been knocked out!" << endl << endl; }
										isAttackSuccessful = true;
									}
								}
								else
								{
									int ourTeamKnockedOut = 0;
									for (int i = 0; i < teamList.size(); i++)
									{
										if (Members[i]->isKnockedOut() == false)
										{
											ourTeamKnockedOut++;
										}
									}
									if (ourTeamKnockedOut == teamList.size())
									{
										isAttackSuccessful = true;
									}
								}
							} while (isAttackSuccessful != true);
						}
					}
				}
			}
		}
		
		///////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////
		////////////////// now check which team won by counting knocked out members.///////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////
		if (ourTeamKnockedOut == teamList.size())
		{
			cout << endl << "Your team has been wiped out! You have lost this battle!" << endl;
			battlecompleted = true;	// exit out the loop since we lost.
			battleResult = false;	// false for we lost.
		}
		else if (theirTeamKnockedOut == EnemyMembers.size())
		{
			cout << endl << "The enemy team has been wiped out! You have won this battle!" << endl;
			battlecompleted = true;	// exit out the loop since we won.
			battleResult = true;	// true for we won.
		}
		else 
		{
			cout << endl << "Turn " << TurnNumber << " has been completed." << endl << endl;
			TurnNumber++;			// After Turn is completed, move to the next turn until either team is wiped out.
		}
		system("PAUSE");			// This allows the user to read what happened.
		system("cls");
	} while (!battlecompleted);
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
				if (Members[i]->isKnockedOut())	// if this party member is knocked out, they gain only half EXP.
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
				if (Members[i]->isKnockedOut())	// if this party member is knocked out, they gain only half EXP.
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
				if (Members[i]->isKnockedOut())	// if this party member is knocked out, they gain only half EXP.
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
				if (Members[i]->isKnockedOut())	// if this party member is knocked out, they gain only half EXP.
				{
					Members[i]->setEXP(5);
				}
				else 
				{
					Members[i]->setEXP(10);
				}
			}
		}
		else {
			cout << "You were taken pity upon by a traveling stranger and was gifted 100 gold for a total of " << gold << endl;
			for (int i = 0; i < teamList.size(); i++) 
			{
				if (Members[i]->isKnockedOut())	// if this party member is knocked out, they gain only half EXP.
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

template <class T>
void Database<T>::healUs() //This function is called in main. Only affects heroes in current party.
{
	gold -= 100;		   // unsure about price, put 100 for now.
	vector<SmashHero*> ourTeam;
	for (int i = 1; i < teamList.size(); i++) 
	{
		ourTeam.push_back(hashTable.getItem(teamList[i]));
		ourTeam[i]->HeroisHealed();
	}
}

template <class T>
void Database<T>::GenerateRandomStatsTeam() //called after heroes are purchased or inserted into teamList vector.
{
	vector<SmashHero*> ourTeam;
	for (int i = 1; i < teamList.size(); i++) 
	{
		ourTeam.push_back(hashTable.getItem(teamList[i]));
		ourTeam[i]->GenerateStats();	   //generate their stats.
	}
}

template <class T>
void Database<T>::GenerateRandomEnemyTeam(vector<SmashHero*>& EnemyMembers)	// This function is only called in teamBattle() when creating an enemy team.
{
	for (int i = 0; i < teamList.size(); i++) 
	{
		int rngesus = rand() % 100 + 1;
		if (rngesus > 98) 
		{
			rngesus = rand() % 6;
		}
		else if (rngesus > 85) 
		{
			rngesus = rand() % 3 + 6;
		}
		else if (rngesus > 60) 
		{
			rngesus = rand() % 24 + 9;
		}
		else 
		{
			rngesus = rand() % 24 + 33;
		}

		//Finding the hero in the hero list and creating it
		string line;
		this->heroList.seekg(0);
		for (int i = 0; i < rngesus; i++) 
		{
			getline(this->heroList, line);
		}
		this->heroList.seekg(0);
		SmashHero* tempPtr = new SmashHero(line);
		EnemyMembers.push_back(tempPtr);
	}
}

template <class T>
Database<T>::~Database() 
{
	saveToFile();
}

#endif DATABASE_H