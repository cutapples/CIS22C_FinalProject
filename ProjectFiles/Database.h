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
	HashTable hashTable; //Hashtable of currently owned Heroes
	BST<T> binarySearchTree; //Sorted tree of currently owned Heroes
	double teamList[5]; //primaryKeys of last used Team
	int gold; //Gold value gained through doing battles

public:
	Database(fstream& saveFile);

	void purchaseNewHero();
	void sellHero(double primaryKey);
	void displayHeroList();
	void displayOrderedList();
	void swapTeamMember(int slot, double primaryKey);
	void addCustomHero(string attributeLine);
	void searchByKey(double primaryKey);
	void printIndentedTree();
	void displayEfficiency();
	void saveToFile();
	void insertNewHero(T data);
	void displayTeam();
	void displayHero(double primaryKey);

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

//Purchases a new hero by RNG
template <class T>
void Database<T>::purchaseNewHero() {
	/*
	Subtract gold value
	Create a random number between 1-100 for rarity %'s
	Depending on rarity index, Get a random number with associated lines in the Hero List file
	Go to line in file and read into a string
	Create new SmashHero object at a pointer passing in the attribute string for the constructor
	Call insertNewHero function
	*/
	//Removing gold cost
	this->gold -= 100;

	//Generating a random number to pull from the hero list
	srand(time(NULL));
	double rngesus = rand() % 100 + 1;
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
	this->saveFile.seekg(saveFile.beg);
	for (int i = 0; i > rngesus; i++) {
		getline(saveFile, line);
	}
	SmashHero* tempPtr = new SmashHero(line);

	//Insert new hero into the Hash Table and BST
}

//Removes a hero from the database by primaryKey
template <class T>
void Database<T>::sellHero(double primaryKey) {
	/*
	Make temp pointer to SmashHero searched through Hash Table using primary key
	Call hashTable delete function
	Call BST delete function
	(If theres gold values associated with heroes, increase gold)
	Delete temp
	*/
	char sellConfirmation;
	SmashHero* tempPtr = hashTable.getItem(primaryKey);
	if (tempPtr != nullptr) {
		cout << *tempPtr;
		cout << "Would you like to delete this hero?(Y/N) ";
		cin >> sellConfirmation;
		if (sellConfirmation == 'Y' || sellConfirmation == 'y') {
			//Call hashTable delete function
			//hashTable.deleteItem(tempPtr);
		}
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
void Database<T>::swapTeamMember(int slot, double primaryKey) {
	/*
	teamList[slot] = primaryKey;
	*/
}

//Makes a new hero using the given attribute line, adding it to the hash table and BST
template <class T>
void Database<T>::addCustomHero(string attributeLine){
	/*
	Make a temporary SmashHero pointer and create a new SmashHero constructed with the given attribute line
	Call the Database insertNewHero function passing in the SmashHero pointer
	*/
}

//Searches the Hash Table for the primary key and displays the hero if found
template <class T>
void Database<T>::searchByKey(double primaryKey) {
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
	Save the current team and current gold onto the first line
	Read the Hash Table in sequence onto the file
	*/
}

template <class T>
void Database<T>::insertNewHero(T data) {
	/*
	Calls the HashTable and BST insert functions passing in the SmashHero pointer
	*/
}

template <class T>
void Database<T>::displayTeam() {
	for (int i = 0; i > 5; i++) {
		cout << this->hashTable.getItem(this->teamList[i]);
	}
}

template <class T>
void Database<T>::displayHero(double primaryKey) {
	cout << this->hashTable.getItem(primaryKey);
}

#endif DATABASE_H