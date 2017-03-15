#ifndef DATABASE_H
#define DATABASE_H

#include "Hashtable.h"
#include "BST.h"
#include "SmashHero.h"

#include <ctime>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Database {
private:
	fstream saveFile; //The file used to load and save data from
	fstream heroList; //List of potential heroes you can get
	HashTable hashTable; //Hashtable of currently owned Heroes
	BST<T> binarySearchTree; //Sorted tree of currently owned Heroes
	int teamList[5]; //primaryKeys of last used Team
	int gold; //Gold value gained through doing battles

public:
	Database(fstream& saveFile);

	SmashHero* purchaseNewHero(int goldCost);
	void teamBattle();
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
void Database<T>::teamBattle() {

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